#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int ALPHA_SIZE = 10;
struct GSAM
{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int link;
        int len;
        Node():next{},link{},len{}{}
    };
    vector<Node>t;
    static constexpr int root = 1;

    GSAM()
    {
        init();
    }

    void init()
    {
        t.assign(2,{});
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int num(char c)
    {
        return c - 'a';
    }

    void insert(const vector<int>& v)//insert trie
    {
        int p = root;
        for(auto x : v){
            if(t[p].next[x] == 0){
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
        }
        return;
    }

    void insert(const string& s)//insert trie
    {
        int p = root;
        for(auto c : s){
            if(next(p,c) == 0){
                next(p,c) = newNode();
            }
            p = next(p,c);
        }
        return;
    }

    int insertSAM(int last, int x)//return last
    {
        int cur = t[last].next[x];
        t[cur].len = t[last].len + 1;
        int p = t[last].link;
        while(p != 0 && t[p].next[x] == 0){
            t[p].next[x] = cur;
            p = t[p].link;
        }
       
        if(p == 0){
            t[cur].link = 1;
        }
        else{
            int q = t[p].next[x];
            if(t[p].len + 1 == t[q].len){
                t[cur].link = q;
            }
            else{
                int clone = newNode();
              
                //t[clone].next = t[q].next;
                for(int i = 0;i < ALPHA_SIZE;i++){
                    t[clone].next[i] = t[t[q].next[i]].len != 0 ? t[q].next[i] : 0;
                }
                t[clone].link = t[q].link;
                t[clone].len = t[p].len + 1;
                while(p != 0 && t[p].next[x] == q){
                    t[p].next[x] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        return cur;
    }

    void build()
    {
        queue<pair<int,int>>q;
        for(int i = 0;i < ALPHA_SIZE;i++){
            if(t[root].next[i] != 0){
                q.push(make_pair(root,i));
            }
        }

        while(!q.empty()){
            auto [la, x] = q.front();
            q.pop();
            int last = insertSAM(la,x);
            for(int i = 0;i < ALPHA_SIZE;i++){
                if(t[last].next[i] != 0){
                    q.push(make_pair(last,i));
                }
            }
        }
    }

    inline int& next(const int& p,const char& c)noexcept
    {
        return t[p].next[num(c)];
    }

};

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
    int n,c;
    cin>>n>>c;
    vector<int>clr(n);
    for(int i = 0;i < n;i++){
        cin>>clr[i];
    }
    
    //vector<vector<int>>g(n);
    HLD h(n);
    vector<int>deg(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        h.addEdge(u,v);
        deg[u]++;
        deg[v]++;
        //g[u].push_back(v);
        //g[v].push_back(u);
    }
    h.work();
    auto&g = h.adj;
    auto&fa = h.parent;
    auto&dep = h.dep;
    GSAM sam;
    auto add = [&](int u, int v)->void
    {
        int lca = h.lca(u,v);
        vector<int>vec;
        vec.reserve(dep[u] + dep[v] - dep[lca] * 2 + 1);
        while(u != lca){
            vec.push_back(clr[u]);
            u = h.rootedParent(lca,u);
        }
        vec.push_back(clr[lca]);
        vector<int>buf;
        buf.reserve(dep[v] - dep[lca]);
        while(v != lca){
            buf.push_back(clr[v]);
            v = h.rootedParent(lca,v);
        }
        for(int i = buf.size() - 1; i >= 0;i--){
            vec.push_back(buf[i]);
        }
        sam.insert(vec);
        reverse(vec.begin(),vec.end());
        sam.insert(vec);
        // cerr<<"insert"<<endl;
        // for(auto x : vec){
        //     cerr<<x<<" ";
        // }
        // cerr<<endl;
        return;
    };
    
    vector<int>leaf;
    for(int i = 0;i < n;i++){
        if(deg[i] == 1)leaf.push_back(i);
    }
    int l = leaf.size();
    for(int i = 0;i < l;i++){
        for(int j = i;j < l;j++){
            add(leaf[i],leaf[j]);
        }
    }
    sam.build();

    auto& t = sam.t;
    int m = t.size();
    ll ans = 0;
    for(int i = 2;i < m;i++){
        ans += t[i].len - t[t[i].link].len;
    }
    cout<<ans<<endl;
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