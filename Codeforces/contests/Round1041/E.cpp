#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in, out, seq;
    vector<vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
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
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
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

    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedParent(int u, int v) {
        swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
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
 };

void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>w(n),clr(n);
    map<int,vector<int>>mp;
    for(int i = 0;i < n;i++){
        cin>>w[i];
    }
    for(int i = 0;i < n;i++){
        cin>>clr[i];
        if(clr[i] != 0)mp[clr[i]].push_back(i);
    }
    HLD hld(n);
    //vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        hld.addEdge(u,v);
        //g[u].push_back(v);
        //g[v].push_back(u);
    }
    //vector<int>dfn(n);
    //int tot = 0;
    int root = 0;
    hld.work(root);
    // auto dfs = [&](auto&&self ,int p, int fa)->void
    // {
    //     dfn[p] = tot++;
    //     for(auto s : g[p]){
    //         if(s != fa){
    //             self(self, s, p);
    //         }
    //     }
    //     return;
    // };
    // dfs(dfs, root, -1);
    auto &dfn = hld.in;
    auto &g = hld.adj;

    for(auto [c, vec] : mp){
        sort(vec.begin(),vec.end(),[&](int i, int j)->bool
        {
            return dfn[i] < dfn[j];
        });
        for(int i = 0;i < vec.size() - 1;i++){
            int lca = hld.lca(vec[i],vec[i + 1]);
            if(clr[lca] == 0){
                clr[lca] = c;
                mp[c].push_back(lca);
            }
        }
    }

    if(clr[root] == 0){
        clr[root] = 1;
        mp[1].push_back(root);
    }
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        if(clr[p] == 0){
            clr[p] = clr[fa];
            mp[clr[p]].push_back(p);
        }
        for(auto s : g[p]){
            self(self, s, p);
        }
    };
    dfs(dfs,0,-1);

    //calc 

    vector<int>cute(n);
    for(auto [c, vec] : mp){
        sort(vec.begin(),vec.end(),[&](int i, int j)->bool
        {
            return dfn[i] < dfn[j];
        });
        for(int i = 0;i < vec.size() - 1;i++){
            int lca = hld.lca(vec[i],vec[i + 1]);
            if(clr[lca] != clr[vec[i]]){
                cute[lca] = true;
            }
        }
    }

    ll ans = 0;
    for(int i = 0;i < n;i++){
        if(cute[i])ans += w[i];
    }

    cout<<ans<<endl;
    for(int i = 0;i < n;i++){
        cout<<clr[i]<<" ";
    }
    cout<<endl;

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