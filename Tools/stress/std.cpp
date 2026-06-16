#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    int cur;

    HLD() {}
    HLD(int n) { init(n); }

    void init(int n) {
        this->n = n;
        siz.assign(n, 0);
        top.assign(n, 0);
        dep.assign(n, 0);
        parent.assign(n, -1);
        in.assign(n, 0);
        out.assign(n, 0);
        seq.assign(n, 0);
        adj.assign(n, {});
        cur = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }

    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];

            if (siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }

    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;

        for (auto v : adj[u]) {
            top[v] = (v == adj[u][0] ? top[u] : v);
            dfs2(v);
        }

        out[u] = cur;
    }
};

static constexpr int K = 21;

struct Info {
    int len = 0;
    i64 ans = 0;

    bool whole = true;
    int full = 0;

    int ps = 0, ss = 0;

    int pm[K], pc[K]; // prefix mask / count
    int sm[K], sc[K]; // suffix mask / count
};

void add_pref(Info &x, int mask, int cnt) {
    if (cnt == 0) return;

    if (x.ps > 0 && x.pm[x.ps - 1] == mask) {
        x.pc[x.ps - 1] += cnt;
    } else {
        x.pm[x.ps] = mask;
        x.pc[x.ps] = cnt;
        x.ps++;
    }
}

void add_suff(Info &x, int mask, int cnt) {
    if (cnt == 0) return;

    if (x.ss > 0 && x.sm[x.ss - 1] == mask) {
        x.sc[x.ss - 1] += cnt;
    } else {
        x.sm[x.ss] = mask;
        x.sc[x.ss] = cnt;
        x.ss++;
    }
}

Info single_info(int a) {
    Info x;
    x.len = 1;
    x.ans = 1;
    x.whole = true;
    x.full = a;

    x.ps = x.ss = 1;
    x.pm[0] = x.sm[0] = a;
    x.pc[0] = x.sc[0] = 1;

    return x;
}

i64 cross_count(const Info &a, const Info &b) {
    // Count legal suffix(a) + prefix(b).
    // a.sm and b.pm are both monotone by set inclusion.
    i64 pref_sum[K];

    i64 s = 0;
    for (int i = 0; i < b.ps; i++) {
        s += b.pc[i];
        pref_sum[i] = s;
    }

    i64 res = 0;
    int j = b.ps - 1;

    for (int i = 0; i < a.ss; i++) {
        while (j >= 0 && (a.sm[i] & b.pm[j])) {
            j--;
        }

        if (j >= 0) {
            res += 1LL * a.sc[i] * pref_sum[j];
        }
    }

    return res;
}

Info merge_info(const Info &a, const Info &b) {
    if (a.len == 0) return b;
    if (b.len == 0) return a;

    Info c;
    c.len = a.len + b.len;

    c.ans = a.ans + b.ans + cross_count(a, b);

    c.whole = a.whole && b.whole && ((a.full & b.full) == 0);
    c.full = c.whole ? (a.full | b.full) : 0;

    c.ps = 0;
    for (int i = 0; i < a.ps; i++) {
        add_pref(c, a.pm[i], a.pc[i]);
    }

    if (a.whole) {
        for (int i = 0; i < b.ps; i++) {
            if (a.full & b.pm[i]) break;
            add_pref(c, a.full | b.pm[i], b.pc[i]);
        }
    }

    c.ss = 0;
    for (int i = 0; i < b.ss; i++) {
        add_suff(c, b.sm[i], b.sc[i]);
    }

    if (b.whole) {
        for (int i = 0; i < a.ss; i++) {
            if (b.full & a.sm[i]) break;
            add_suff(c, b.full | a.sm[i], a.sc[i]);
        }
    }

    return c;
}

Info rev_info(const Info &a) {
    Info b = a;

    b.ps = a.ss;
    for (int i = 0; i < a.ss; i++) {
        b.pm[i] = a.sm[i];
        b.pc[i] = a.sc[i];
    }

    b.ss = a.ps;
    for (int i = 0; i < a.ps; i++) {
        b.sm[i] = a.pm[i];
        b.sc[i] = a.pc[i];
    }

    return b;
}

struct SegTree {
    int n = 0;
    int size = 1;
    vector<Info> t;

    SegTree() {}

    SegTree(const vector<int> &base) {
        build(base);
    }

    void build(const vector<int> &base) {
        n = (int)base.size();

        size = 1;
        while (size < n) size <<= 1;

        t.assign(size << 1, Info{});

        for (int i = 0; i < n; i++) {
            t[size + i] = single_info(base[i]);
        }

        for (int i = size - 1; i >= 1; i--) {
            t[i] = merge_info(t[i << 1], t[i << 1 | 1]);
        }
    }

    Info query(int l, int r) const {
        // [l, r), in HLD order.
        Info left, right;

        l += size;
        r += size;

        while (l < r) {
            if (l & 1) {
                left = merge_info(left, t[l]);
                l++;
            }

            if (r & 1) {
                r--;
                right = merge_info(t[r], right);
            }

            l >>= 1;
            r >>= 1;
        }

        return merge_info(left, right);
    }
};

void solve_one() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    HLD hld(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        hld.addEdge(u, v);
    }

    hld.work(0);

    vector<int> base(n);
    for (int i = 0; i < n; i++) {
        base[i] = a[hld.seq[i]];
    }

    SegTree seg(base);

    vector<Info> chain_pref(n);

    for (int pos = 0; pos < n; pos++) {
        int u = hld.seq[pos];
        Info cur = single_info(a[u]);

        if (u == hld.top[u]) {
            chain_pref[u] = cur;
        } else {
            chain_pref[u] = merge_info(chain_pref[hld.parent[u]], cur);
        }
    }

    auto path_query = [&](int x, int y) -> i64 {
        Info left, right;

        while (hld.top[x] != hld.top[y]) {
            if (hld.dep[hld.top[x]] > hld.dep[hld.top[y]]) {
                // Path direction: x -> top[x].
                Info cur = rev_info(chain_pref[x]);
                left = merge_info(left, cur);

                x = hld.parent[hld.top[x]];
            } else {
                // Path direction: top[y] -> y.
                Info cur = chain_pref[y];
                right = merge_info(cur, right);

                y = hld.parent[hld.top[y]];
            }
        }

        if (hld.dep[x] > hld.dep[y]) {
            // Same chain, need x -> y, but HLD order gives y -> x.
            Info cur = seg.query(hld.in[y], hld.in[x] + 1);
            left = merge_info(left, rev_info(cur));
        } else {
            // Same chain, HLD order is already x -> y.
            Info cur = seg.query(hld.in[x], hld.in[y] + 1);
            left = merge_info(left, cur);
        }

        return merge_info(left, right).ans;
    };

    while (q--) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;

        cout << path_query(x, y) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        solve_one();
    }

    return 0;
}