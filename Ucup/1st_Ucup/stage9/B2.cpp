#include <bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

// B.cpp Create time : 2026.01.30

struct Edge {
    int to, id;
};

static inline void addColor(vector<int> &cnt, vector<int> &tp, int &mx, int c, int dv) {
    int old = cnt[c];
    if (old) tp[old]--;
    int now = old + dv;
    cnt[c] = now;
    if (now) tp[now]++;
    if (now > mx) mx = now;
    while (mx > 0 && tp[mx] == 0) mx--;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // compress answers to [0, k)
    auto sa = a;
    sort(sa.begin(), sa.end());
    sa.erase(unique(sa.begin(), sa.end()), sa.end());
    int k = (int)sa.size();
    for (int i = 0; i < n; i++) {
        a[i] = (int)(lower_bound(sa.begin(), sa.end(), a[i]) - sa.begin());
    }

    vector<int> U(m), V(m);
    vector<vector<Edge>> adj(n);
    adj.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        U[i] = u, V[i] = v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    // 1) find bridges in multigraph (iterative DFS)
    vector<int> dfn(n, 0), low(n, 0), it(n, 0), par(n, -1), pe(n, -1);
    vector<char> isBridge(m, 0);
    int timer = 0;

    for (int s = 0; s < n; s++) if (!dfn[s]) {
        vector<int> st;
        st.push_back(s);
        par[s] = -1;
        pe[s] = -1;

        while (!st.empty()) {
            int u = st.back();
            if (!dfn[u]) dfn[u] = low[u] = ++timer;

            if (it[u] == (int)adj[u].size()) {
                st.pop_back();
                int p = par[u];
                if (p != -1) {
                    low[p] = min(low[p], low[u]);
                    if (low[u] > dfn[p]) {
                        isBridge[pe[u]] = 1;
                    }
                }
                continue;
            }

            auto [v, id] = adj[u][it[u]++];
            if (id == pe[u]) continue;

            if (!dfn[v]) {
                par[v] = u;
                pe[v] = id;
                st.push_back(v);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    // 2) contract components by removing bridges
    vector<int> bel(n, -1);
    int cnt = 0;
    for (int i = 0; i < n; i++) if (bel[i] == -1) {
        vector<int> st = {i};
        bel[i] = cnt;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (auto [v, id] : adj[u]) {
                if (isBridge[id]) continue;
                if (bel[v] == -1) {
                    bel[v] = cnt;
                    st.push_back(v);
                }
            }
        }
        cnt++;
    }

    // 3) build bridge forest on components, store original edge id
    vector<vector<pair<int,int>>> tr(cnt); // (to, edge_id)
    for (int i = 0; i < m; i++) {
        int cu = bel[U[i]], cv = bel[V[i]];
        if (cu == cv) continue;
        tr[cu].push_back({cv, i});
        tr[cv].push_back({cu, i});
    }

    // values inside each component
    vector<vector<int>> vals(cnt);
    vector<int> w(cnt, 0);
    for (int i = 0; i < n; i++) {
        vals[bel[i]].push_back(a[i]);
    }
    for (int c = 0; c < cnt; c++) w[c] = (int)vals[c].size();

    // answer = base + delta[edge] (delta only for bridges, else 0)
    vector<i64> delta(m, 0);

    // DSU globals per test
    vector<int> cntIn(k, 0), cntOut(k, 0);
    vector<int> visColor(k, 0), touched;
    int tag = 1;

    vector<int> parent(cnt, -1), peid(cnt, -1), heavy(cnt, -1);
    vector<int> subw(cnt, 0);
    vector<char> seen(cnt, 0), big(cnt, 0);

    i64 base = 0;

    // upd subtree(u) excluding big-child subtrees
    auto upd = [&](int root, int fa, int val,
                   vector<int> &tp, vector<int> &tp2, int &Max, int &Max2) {
        vector<pair<int,int>> st;
        st.push_back({root, fa});
        while (!st.empty()) {
            auto [u, p] = st.back();
            st.pop_back();

            for (int col : vals[u]) {
                addColor(cntIn,  tp,  Max,  col,  val);
                addColor(cntOut, tp2, Max2, col, -val);
            }
            for (auto [v, id] : tr[u]) {
                if (v == p || big[v]) continue;
                st.push_back({v, u});
            }
        }
    };

    // process each tree in the bridge forest
    for (int r = 0; r < cnt; r++) if (!seen[r]) {
        // build parent order (iterative)
        vector<int> order;
        order.reserve(1024);
        vector<int> st = {r};
        parent[r] = -1;
        peid[r] = -1;
        seen[r] = 1;

        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            order.push_back(u);
            for (auto [v, id] : tr[u]) if (v != parent[u]) {
                if (!seen[v]) {
                    seen[v] = 1;
                    parent[v] = u;
                    peid[v] = id;
                    st.push_back(v);
                }
            }
        }

        // compute subtree weights and heavy child in reverse order
        for (int u : order) {
            subw[u] = w[u];
            heavy[u] = -1;
            big[u] = 0;
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int u = order[i];
            for (auto [v, id] : tr[u]) if (v != parent[u]) {
                subw[u] += subw[v];
                if (heavy[u] == -1 || subw[v] > subw[heavy[u]]) heavy[u] = v;
            }
        }

        // tree total weight
        int treeW = 0;
        for (int u : order) treeW += w[u];

        vector<int> tp(treeW + 1, 0), tp2(treeW + 1, 0);
        int Max = 0, Max2 = 0;

        // init: S empty, complement = whole tree
        tag++;
        touched.clear();
        for (int u : order) {
            for (int col : vals[u]) {
                if (visColor[col] != tag) {
                    visColor[col] = tag;
                    touched.push_back(col);
                }
                addColor(cntOut, tp2, Max2, col, +1);
            }
        }
        int bestTree = Max2;
        base += bestTree;

        // DSU on tree with explicit stack simulating dfs2(u, keep)
        struct Frame {
            int u, fa;
            bool keep;
            int stage; // 0: light, 1: heavy, 2: work/cleanup
        };
        vector<Frame> stk;
        stk.push_back({r, -1, false, 0});

        while (!stk.empty()) {
            auto fr = stk.back();
            stk.pop_back();
            int u = fr.u, fa = fr.fa;
            bool keep = fr.keep;

            if (fr.stage == 0) {
                // after light children, go stage 1
                stk.push_back({u, fa, keep, 1});
                // push light children (keep=false)
                for (auto [v, id] : tr[u]) {
                    if (v == fa || v == heavy[u]) continue;
                    stk.push_back({v, u, false, 0});
                }
            } else if (fr.stage == 1) {
                // after heavy child, go stage 2
                stk.push_back({u, fa, keep, 2});
                if (heavy[u] != -1) {
                    stk.push_back({heavy[u], u, true, 0});
                }
            } else {
                // stage 2: heavy has been kept in DS
                if (heavy[u] != -1) big[heavy[u]] = 1;

                upd(u, fa, +1, tp, tp2, Max, Max2);

                if (fa != -1) {
                    int eid = peid[u]; // bridge edge between u-fa
                    delta[eid] = (i64)Max + (i64)Max2 - (i64)bestTree;
                }

                if (heavy[u] != -1) big[heavy[u]] = 0;

                if (!keep) {
                    upd(u, fa, -1, tp, tp2, Max, Max2);
                }
            }
        }

        // reset cntIn/cntOut for colors used in this tree
        for (int col : touched) {
            cntIn[col] = 0;
            cntOut[col] = 0;
        }
    }

    // output answers for each bug edge
    // non-bridge => delta = 0; bridge => delta computed at child side
    for (int i = 0; i < m; i++) {
        i64 ans = base + delta[i];
        cout << ans << " \n"[i == m - 1];
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--){
        solve();
    }
    return 0;
}
