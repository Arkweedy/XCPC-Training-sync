#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
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
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
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
    
    int intersection(int x, int y, int u, int v)
    {
        vector<int>t = {lca(x, u), lca(x, v), lca(y, u), lca(y, v)};
        sort(t.begin(), t.end());
        int l = lca(x, y), r = lca(u, v);
        if (dep[l] > dep[r])swap(l, r);
        if (dep[t[0]] < dep[l] || dep[t[2]] < dep[r]) {
            return 0;
        }
        return 1 + dist(t[2], t[3]);
    }
};

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n * 2);
    vector<int>ilock(n + 1),ikey(n + 1);
    for(int i = 0;i < n * 2;i++){
        cin>>a[i];
        if(a[i] > 0)ikey[a[i]] = i;
        else ilock[-a[i]] = i;
    }
    HLD hld(n * 2);
    vector<vector<int>>g(n * 2);
    for(int i = 0;i < n * 2 - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        hld.addEdge(u,v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int root = ilock[1];
    hld.work(root);
    const auto &fa = hld.parent;
    vector<int>clr(n * 2);
    for(int i = 1;i <= n;i++){
        if(hld.isAncester(ilock[i],ikey[i])){
            clr[ilock[i]] = 1;
        }
    }
   

    vector<int>have(n * 2);
    int Deadlock = 0;
    int depest_clred = root;
    auto check = [&](auto&&self, int p)->int
    {
        int clred_son = 0;
        if(clr[p])depest_clred = p;
        for(auto s : g[p]){
            if(s != fa[p])
                clred_son += self(self, s);
        }
        if(clred_son >= 2)Deadlock = 1;
        if(clred_son || clr[p])return 1;
        else return 0;
    };
    
    
 
    for(auto s : g[root]){
        if(hld.isAncester(s,ikey[1]) || s == ikey[1]){
            
            check(check,s);
            break;
        }
    }
    if(Deadlock){
        string ans(n, '0');
        cout<<ans<<endl;
        return;
    }

    int bg = -1;
    for(auto s : g[depest_clred]){
        if(s != fa[depest_clred]){
            if(hld.rootedLca(s,depest_clred,ikey[-a[depest_clred]]) == s){
                bg = s;
            }
        }
    }

    assert(bg != -1);


    if(a[bg] < 0){
        string ans(n, '0');
        cout<<ans<<endl;
        return;
    }
    //bfs
    queue<int>q;
    vector<int>vskey(n + 1),vslock(n + 1);
    vector<int>vs(n * 2);
    vskey[a[bg]] = 1;
    q.push(bg);
    while(!q.empty()){
        int p = q.front();
        vs[p] = true;
        q.pop();
        for(auto s : g[p]){
            if(vs[s])continue;
            if(a[s] > 0){
                vskey[a[s]] = 1;
                q.push(s);
                if(vslock[a[s]] == 1){
                    q.push(ilock[a[s]]);
                }
            }
            else{
                vslock[-a[s]] = 1;
                if(vskey[-a[s]]){
                    q.push(s);
                }
            }
        }
    }

    if(count(vs.begin(),vs.end(),1) != n * 2){
        string ans(n, '0');
        cout<<ans<<endl;
        return;
    }
    else{
        queue<int>q;
        vector<int>vs(n * 2);
        q.push(bg);
        string ans(n,'0');
        while(!q.empty()){
            
            int p = q.front();
            vs[p] = 1;
            q.pop();
            ans[a[p] - 1] = '1';
            for(auto s : g[p]){
                if(!vs[s] && a[s] > 0){
                    q.push(s);
                }
            }
        }
        cout<<ans<<endl;
    }

    return;
    //min on tree
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