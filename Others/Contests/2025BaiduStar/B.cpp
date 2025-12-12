#include<bits/stdc++.h>

using namespace std;
using ll = long long;

template<typename T>
struct MinCostFlow
{
    struct _Edge{
        int to;
        T cap;
        T cost;
        _Edge(int to_, T cap_, T cost_) : to(to_), cap(cap_), cost(cost_){}
    };

    int n;
    vector<_Edge>e;
    vector<vector<int>>g;
    vector<T>h, dis;
    vector<int>pre;

    bool dijkstra(int s, int t)
    {
        dis.assign(n, std::numeric_limits<T>::max());
        pre.assign(n ,-1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>>que;
        dis[s] = 0;
        que.emplace(0,s);
        while(!que.empty()){
            T d = que.top().first;
            int u = que.top().second;
            que.pop();
            if(dis[u] != d){
                continue;
            }
            for(int i : g[u]){
                int v = e[i].to;
                T cap = e[i].cap;
                T cost = e[i].cost;
                if(cap > 0 && dis[v] > d + h[u] - h[v] + cost){
                    dis[v] = d + h[u] - h[v] + cost;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
         
            }
        }
        return dis[t] != std::numeric_limits<T>::max();
    }

    MinCostFlow(){}
    MinCostFlow(int n){init(n);}

    void init(int n_)
    {
        n = n_;
        e.clear();
        g.assign(n, {});
    }

    void addEdge(int u, int v, T cap, T cost)
    {
        //cerr << "add " <<u  << " " << v << " " << cap <<" " <<cost << endl;
        g[u].push_back(e.size());
        e.emplace_back(v,cap, cost);
        g[v].push_back(e.size());
        e.emplace_back(u, 0 ,-cost);
    }

    pair<T, T>flow(int s, int t)
    {
        T flow = 0;
        T cost = 0;
        h.assign(n, 0);
        while(dijkstra(s, t)){
            for(int i = 0;i < n;++i){
                h[i] += dis[i];
            }
            T aug = std::numeric_limits<T>::max();
            for(int i = t;i != s; i = e[pre[i] ^ 1].to){
                aug = min(aug, e[pre[i]].cap);
            }
            for(int i = t;i != s;i = e[pre[i] ^ 1].to){
                e[pre[i]].cap -= aug;
                e[pre[i]^1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return make_pair(flow, cost);
    }
};

void solve()
{
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    int s = 0, t = n * 2 + m * 2 + 1;
    //0 s
    // 1~n 
    // n+1~2n
    // 2n+1 ~ 2n+2m 
    MinCostFlow<int>f(n * 2 + m * 2 + 2);
    //cerr << s << " " << t << endl;
    constexpr int inf = 1e5;
    for(int i = 0;i < k;i++){
        int x;
        cin >> x;
        f.addEdge(s, x, 1, 0);
    }
    for(int i = 0;i < l;i++){
        int x;
        cin >> x;
        x += n;
        f.addEdge(x, t, 1, 0);
    }
    for(int i = 0;i < m;i++){
        int c, p , q;
        cin >> c >> p >> q;
        int u = n * 2 + i + 1;
        int v = n * 2 + i + 1 + m;
        f.addEdge(u, v, c, 1);
        for(int j = 0;j < p;j++){
            int x;
            cin >> x;
            f.addEdge(x, u, inf, 0);
        }
        for(int j = 0;j < q;j++){
            int x;
            cin >> x;
            f.addEdge(v, x, inf, 0);
        }
    }
    for(int i = 1;i <= n;i++){
        f.addEdge(i, i + n, inf, 0);
    }
    auto res = f.flow(s, t);
    int all = k;
    //cerr << res.first << " " << res.second << endl;
    if(res.first != all){
        cout << -1 << endl;
    }
    else{
        cout << res.second << endl;
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt ;
    while(tt--){
        solve();
    }
    return 0;
}