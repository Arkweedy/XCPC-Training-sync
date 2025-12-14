#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct VBCC {
    int n;  // 原始图的节点数
    vector<vector<int>> adj;
    vector<vector<int>> col;  // 存储每个点双连通分量包含的节点
    vector<int> dfn, low;
    vector<int> stk;
    int cur, cnt;     // 时间戳计数器和点双连通分量计数器
    vector<int> cut;  // 标记每个节点是否为割点

aaa

    VBCC(int n) { init(n); }

    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        col.assign(n, {});
        cut.assign(n, 0);
        stk.clear();
        cnt = cur = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void tarjan(int x, int root) {
        low[x] = dfn[x] = cur++;
        stk.push_back(x);
        if (x == root && !adj[x].size()) {
            col[cnt++].push_back(x);
            return;
        }

        int flg = 0;
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                tarjan(y, root);

                low[x] = min(low[x], low[y]);

                if (dfn[x] <= low[y]) {
                    flg++;
                    if (x != root || flg > 1) {
                        cut[x] = 1;
                    }
                    int pre = 0;
                    do {
                        pre = stk.back();
                        col[cnt].push_back(pre);
                        stk.pop_back();
                    } while (pre != y);
                    col[cnt++].push_back(x);
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }

    void work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                tarjan(i, i);
            }
        }
    }

    // 新图（圆方树）的结构体定义
    struct Graph {
        int n;                         // 新图的节点数量
        //vector<pair<int, int>> edges;  // 新图的边集
        vector<vector<int>>e;
    };

    Graph compress() {
        // 节点编号规则：
        // 0 到 n - 1 是 圆点 代表原图中的点
        // n 开始是 方点 代表点双连通分量

        Graph g;
        g.n = n + cnt;
        g.e.assign(g.n,{});
        // 构建新图的边
        for (int i = 0; i < cnt; i++) {
            for (auto u : col[i]) {
                g.e[u].push_back(i+n);
                g.e[i+n].push_back(u);
            }    
        }

        return g;
    }
};

vector<int>f;
int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

void solve()
{
    int n,m;cin>>n>>m;
    f.resize(n);
    iota(f.begin(),f.end(),0);
    set<pair<int,int>>s;
    VBCC g(n);
    vector<int>deg(n);

    while(m--){
        int u,v;cin>>u>>v;
        u--,v--;
        if(!s.count({u,v}) && !s.count({v,u})&& u != v){
            s.insert({u,v});
            g.addEdge(u,v);
            deg[u]++,deg[v]++;
        }
    }
    
    if(n==3){
        cout<<"No\n";
        return;
    }

    g.work();
    
    auto [c,e] = g.compress();

    for(int i=0;i<n;i++){
        if(e[i].size() > n/2){
            cout<<"No\n";
            return;
        }
    }
    
    vector<int>dep(c), fa(c,-1);
    auto dfs = [&](auto &&self,int u,int f)->void
    {
        for(auto v:e[u]){
            if(v==f)continue;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            self(self,v,u);
        }
    };

    dfs(dfs,0,-1);

    vector<vector<pair<int,int>>>adj(n);

    for(auto [u,v]:s){
        int be;
        if(dep[u] < dep[v]){
            be = fa[v];
        }else{
            be = fa[u];
        }
        assert(be != -1);
        adj[u].push_back({v,be});
        adj[v].push_back({u,be});
    }

    int u = 0;
    for(int i=0;i<n;i++)if(deg[i] > deg[u])u = i;

    set<pair<int,int>>edges;
    vector<int>vis(c);
    int tot = 0;

    for(auto [v,st]:adj[u]){
        if(vis[st])continue;
        assert(find(u)!=find(v));
        vis[st] = 1;
        edges.insert({u,v});
        f[find(u)] = find(v);
        //cout<<u+1<<' '<<v+1<<endl;
        tot++;
    }

    assert(tot <= n/2);

    for(auto [v,st]:adj[u]){
        if(tot == n / 2)break;
        if(find(u) == find(v))continue;
        f[find(u)] = find(v);
        edges.insert({u,v});
        tot++;
        //cout<<u+1<<' '<<v+1<<endl;
        
    }

    
    for(auto [x,y]:s){
        if(x == u || y == u)continue;
        if(find(x) == find(y))continue;
        edges.insert({x,y});
        f[find(x)] = find(y);
    }

    vector<int>cnt(n);
    for(auto [u,v]:edges){
        cnt[u]++,cnt[v]++;
    }

    int p = -1;
    for(int i=0;i<n;i++){
        if(cnt[i] > n/2){
            p = i;
        }
    }

    if(p != -1){
        vector<int>tag(n);
        for(auto [u,v]:edges){
            if(u == p || v == p){
                tag[u+v-p] = 1;
            }
        }

        tag[u] = 0;

        for(auto [x,y]:s){
            if(tag[y])swap(x,y);
            if(tag[x] && tag[y]){
                edges.insert({x,y});
                edges.erase({x,p});
                edges.erase({p,x});
                break;
            }else if(tag[x] && y == u){
                edges.insert({x,u});
                edges.erase({u,p});
                edges.erase({p,u});
                break;
            }else if(tag[x] && y != p){
                edges.insert({x,y});
                edges.erase({x,p});
                edges.erase({p,x});
                break;
            }
        }
    }

    cout<<"Yes\n";
    for(auto [u,v]:edges){
        cout<<u+1<<' '<<v+1<<'\n';
    }
    
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