#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct KMP
{
    string s;
    vector<int>fail;
    vector<int>slink;
    vector<int>diff;
    vector<vector<int>>ot;
    int suff;

    KMP(){init();}
    KMP(string& ss){init();for(auto ch :ss)add(ch);}

    void init()
    {
        suff = 0;
        s += '#';
        fail.assign(1, 0);
        slink.assign(1, -1);
        diff.assign(1, -1);
        ot.emplace_back();
    }
    

    void newNode()
    {
        fail.emplace_back();
        diff.emplace_back();
        slink.emplace_back();
        ot.emplace_back();
    }

    void add(char c)
    {
        s += c;
        newNode();
        int last = s.length() - 1;
        int cur = suff;
        while(cur != 0 && s[cur + 1] != s[last]){
            cur = fail[cur];
        }
        if(s[last] == s[cur + 1] && last != 1)fail[last] = cur + 1;
        else fail[last] = cur;
        ot[fail[last]].push_back(last);
        suff = fail[last];
    }
    
};

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
    string s;
    cin>>s;
    int n = s.length();
    KMP kmp(s);
    auto &t = kmp.ot;
    auto &fail = kmp.fail;
    HLD hld(n + 1);
    for(int i = 1;i <= n;i++){
        hld.addEdge(i, kmp.fail[i]);
    }
    hld.work();

    // for(int i = 0;i <= n;i++){
    //     cerr<<i<<" "<<fail[i]<<endl;
    // }
    
    int q;
    cin>>q;
    while(q--){
        int u,v;
        cin>>u>>v;
        //u--,v--;
        int p = hld.lca(fail[u],fail[v]);
        cout<<p<<"\n";
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