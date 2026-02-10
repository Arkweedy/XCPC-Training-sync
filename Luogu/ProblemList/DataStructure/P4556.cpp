#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P4556.cpp Create time : 2026.02.09 00:52

struct info
{
    int id, cnt;
    info() :id(0), cnt(0){}
    info(int a, int b):id(a),cnt(b){}
    info operator+(info other)
    {
        if(cnt != other.cnt)return cnt > other.cnt ? *this : other;
        else return id < other.id ? *this : other;
    }
};

vector<int>ls, rs;
vector<info>t;
stack<int>rec;

struct segtree
{
    int n;
    int root;

    segtree():n(0),root(-1){}

    segtree(int n_) = delete;

    void init(int n_)
    {
        n = n_;
        root = newNode();
    }

    int newNode()
    {
        if(!rec.empty()){
            int p = rec.top();
            rec.pop();
            return p;
        }
        else{
            t.emplace_back();
            ls.emplace_back();
            rs.emplace_back();
            return t.size() - 1;
        }
    }

    void apply(int x, int v)
    {
        apply(x, v, 0, n - 1, root);
    }

    void push_up(int p)
    {
        t[p] = {0, 0};
        if(ls[p])t[p] = t[p] + t[ls[p]];
        if(rs[p])t[p] = t[p] + t[rs[p]];
        return;
    }

    void recycle(int p)
    {
        t[p] = info();
        ls[p] = rs[p] = 0;
        rec.push(p);
        return;
    }

    void apply(int x, int v, int l, int r, int p)
    {
       
        if(l == r){
            if(t[p].id != x)t[p] = {x, 0};
            t[p].cnt += v;
            return;
        }
        int m = l + r >> 1;
        if(x <= m){
            if(ls[p] == 0)ls[p] = newNode();
            apply(x, v, l, m, ls[p]);
        }
        else{
            if(rs[p] == 0)rs[p] = newNode();
            apply(x, v, m + 1, r, rs[p]);
        }
        push_up(p);
        return;
    }

    int get()
    {
        if(t[root].cnt == 0){
            return -1;
        }
        else return t[root].id;
    }

    void join(segtree& ot)
    {
        assert(ot.n == n);
        join(root, ot.root, 0, n - 1);
        return;
    }

    void join(int p1, int p2, int l, int r)
    {
        if(l == r){
            t[p1].cnt = t[p1].cnt + t[p2].cnt;
            return;
        }
        int m = l + r >> 1;
        if(ls[p1] && ls[p2])join(ls[p1], ls[p2], l, m);
        else if(ls[p2])ls[p1] = ls[p2];
        if(rs[p1] && rs[p2])join(rs[p1], rs[p2], m + 1, r);
        else if(rs[p2])rs[p1] = rs[p2];
        push_up(p1);
        recycle(p2);
        return;
    }
};

struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;

    HLD() {}
    HLD(int n) { init(n); }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
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
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }

    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }

        int d = dep[u] - k;

        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }

        return seq[in[u] - dep[u] + d];
    }

    bool isAncester(int u, int v) { return in[u] <= in[v] && in[v] < out[u]; }

    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it =
            std::upper_bound(adj[u].begin(), adj[u].end(), v,
                             [&](int x, int y) { return in[x] < in[y]; }) -
            1;
        return *it;
    }

    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }

    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }

    int intersection(int x, int y, int u, int v) {
        vector<int> t = {lca(x, u), lca(x, v), lca(y, u), lca(y, v)};
        sort(t.begin(), t.end());
        int l = lca(x, y), r = lca(u, v);
        if (dep[l] > dep[r]) swap(l, r);
        if (dep[t[0]] < dep[l] || dep[t[2]] < dep[r]) {
            return 0;
        }
        return 1 + dist(t[2], t[3]);
    }
};

constexpr int N = 1e5 + 10;

void solve()
{
    int n, m;
    cin >> n >> m;
    HLD h(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin >> u >> v;
        u--, v--;
        h.addEdge(u, v);
    }
    h.work(0);

    vector<segtree>t(n);
    for(int i = 0;i < n;i++)t[i].init(N);

    for(int i = 0;i < m;i++){
        int x, y, z;
        cin >> x >> y >> z;
        x--, y--, z--;
        int lc = h.lca(x, y);
        int pa = h.parent[lc];
        t[x].apply(z, 1); 
        t[y].apply(z, 1);
        t[lc].apply(z, -1);
        if(pa != -1)t[pa].apply(z, -1);
    }

    vector<int>ans(n);
    auto& g = h.adj;
    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            self(self, s);
            t[p].join(t[s]);
        }
        ans[p] = t[p].get() + 1;
    };
    dfs(dfs, 0);
    

    for(int i = 0;i < n;i++){
        cout << ans[i] << "\n";
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}