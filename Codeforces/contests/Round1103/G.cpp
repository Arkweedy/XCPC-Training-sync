#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.06.12 22:41

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

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    HLD t(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.addEdge(u, v);
    }
    t.work();
    auto& dfn = t.seq;
    auto& dep = t.dep; //dep[root] = 0;
    auto& top = t.top;
    auto& adj = t.adj;
   
    vector<int>fa(n, -1); // except 0;
    for(auto i : t.seq){
        int x = i;
        if(a[i] == 0)x = fa[i];
        for(auto s : adj[i]){
            fa[s] = x;
        }
    }
    
    vector<int>f(n), len(n);
    for(int i = 0;i < n;i++){
        if(a[i] == 0)continue;
        int p = i;
        int mask = a[p];
        while(fa[p] != -1 && (mask & a[fa[p]]) == 0){
            p = fa[p];
            mask |= a[p];   
        }
        if(fa[p] == -1){
            f[i] = 0;
        }
        else{
            f[i] = t.jump(p, dep[p] - dep[fa[p]] - 1);
        }
        len[i] = dep[i] - dep[f[i]] + 1;
    }
    
    for(int i = 0;i < n;i++){
        if(a[i] == 0){
            if(fa[i] == -1){
                f[i] = 0;
                len[i] = dep[i] - dep[f[i]] + 1;
            }
            else{
                f[i] = f[fa[i]];
                len[i] = dep[i] - dep[f[i]] + 1;
            }
        }
    }
    
    vector<i64>v(n), pv(n);
    for(int i = 0;i < n;i++){
        v[i] = len[i];
    }
    for(auto i : t.seq){
        pv[i] += v[i];
        for(auto s : t.adj[i]){
            pv[s] += pv[i];
        }
    }

    int le = __lg(n);
    vector<vector<int>>st(le + 1, vector<int>(n, -1));
    for(int i = 0;i < n;i++){
        st[0][i] = fa[i];
    }
    for(int i = 1;i <= le;i++){
        for(int j = 0;j < n;j++){
            if(st[i - 1][j] != -1)st[i][j] = st[i - 1][st[i - 1][j]];
        }
    }

    int tot = n - 1;
    auto val = v;

    auto find = [&](int u, int k)->int
    {
        int p = u;
        if(dep[f[p]] <= dep[k]){
            fa.emplace_back(u);
            pv.emplace_back(pv[u]);
            val.emplace_back(0);
            dep.emplace_back(dep[u] + 1);
            tot++;
            return tot;
        }

        for(int i = le;i >= 0;i--){
            int x = st[i][p];
            if(x != -1 && dep[f[x]] > dep[k]){
                p = x;
            }
        }
        return p;
    };

    // for(int i = 0;i < n;i++){
    //     cerr << fa[i] << " ";
    // }
    // cerr << endl;
    // for(int i = 0;i < n;i++){
    //     cerr << f[i] << " ";
    // }
    // cerr << endl;
    // for(int i = 0;i < n;i++){
    //     cerr << v[i] << " ";
    // }
    // cerr << endl;

    

    while(q--){
        int u, v;
        cin >> u >> v;
        u--, v--;
        if(u == v){
            cout << 1 << "\n";
            continue;
        }
        if(dep[u] > dep[v])swap(u, v);
        int lc = t.lca(u, v);
        //cerr << u << " " << v << " " << lc << endl;
        i64 res = pv[u] + pv[v] - 2 * pv[lc];
        //cerr << res << endl;
        
        int Lp = find(u, lc), Rp = find(v, lc);
        res -= pv[Lp] - pv[lc] - val[Lp];
        res -= pv[Rp] - pv[lc] - val[Rp];
        //cerr << res << endl;
        vector<int>l, r;
        vector<int>lv,rv;
        int p = Lp;
        int le = dep[Lp] - dep[lc] - 1;
        res += 1ll * le * (le + 1) / 2;
        
        while(fa[p] != -1 && dep[fa[p]] > dep[lc]){
            lv.push_back(dep[p] - dep[fa[p]]);
            p = fa[p];
            l.push_back(p);
        }
        l.push_back(lc);
        lv.push_back(dep[p] - dep[lc]);

        p = Rp;
        le = dep[Rp] - dep[lc] - 1;
        res += 1ll * le * (le + 1) / 2;
        while(fa[p] != -1 && dep[fa[p]] > dep[lc]){
            rv.push_back(dep[p] - dep[fa[p]]);
            p = fa[p];
            r.push_back(p);
        }
        r.push_back(lc);
        rv.push_back(dep[p] - dep[lc]);

        //cerr << res << endl;

        reverse(l.begin(),l.end());
        reverse(r.begin(),r.end());
        reverse(lv.begin(),lv.end());
        reverse(rv.begin(),rv.end());
        int x = l.size(), y = r.size();
        //cerr << x << " " << y << endl;
        vector<int>lmsk(x), rmsk(y);
        for(int i = 0;i < x;i++){
            lmsk[i] = a[l[i]];
            if(i > 0)lmsk[i] |= lmsk[i - 1];
        }
        for(int i = 0;i < y;i++){
            rmsk[i] = a[r[i]];
            if(i > 0)rmsk[i] |= rmsk[i - 1];
        }
        for(int i = 0;i < x;i++){
            for(int j = 0;j < y;j++){
                if((lmsk[i] & rmsk[j]) == a[lc]){
                    res += 1ll * lv[i] * rv[j];
                }
            }
        }
        cout << res << "\n";
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
