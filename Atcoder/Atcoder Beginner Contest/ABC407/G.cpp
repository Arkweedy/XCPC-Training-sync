#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
 struct MinCostFlow {
    struct _Edge {
        int to;
        T cap;
        T cost;
        _Edge(int to_, T cap_, T cost_) : to(to_), cap(cap_), cost(cost_) {}
    };
    int n;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<T> h, dis;
    vector<int> pre;
    bool dijkstra(int s, int t) {
        dis.assign(n, numeric_limits<T>::max());
        pre.assign(n, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            T d = que.top().first;
            int u = que.top().second;
            que.pop();
            if (dis[u] != d) {
                continue;
            }
            for (int i : g[u]) {
                int v = e[i].to;
                T cap = e[i].cap;
                T cost = e[i].cost;
                if (cap > 0 && dis[v] > d + h[u] - h[v] + cost) {
                    dis[v] = d + h[u] - h[v] + cost;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != numeric_limits<T>::max();
    }
    MinCostFlow() {}
    MinCostFlow(int n_) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        e.clear();
        g.assign(n, {});
    }
    void addEdge(int u, int v, T cap, T cost) {
        g[u].push_back(e.size());
        e.emplace_back(v, cap, cost);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -cost);
    }
    pair<T, T> flow(int s, int t) {
        T flow = 0;
        T cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) {
                 h[i] += dis[i];
            }
            T aug = numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                aug = min(aug, e[pre[i]].cap);
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return make_pair(flow, cost);
    }
    struct Edge {
        int from;
        int to;
        T cap;
        T cost;
        T flow;
    };
    vector<Edge> edges() {
        vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.cost = e[i].cost;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
 };

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<vector<ll>>a(n,vector<ll>(m));
    ll sum = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin>>a[i][j];
            sum += a[i][j];
        }
    }
    MinCostFlow<ll> f(n * m + 2);
    int s = n * m ,t = n * m + 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            int p = i * m + j;
            if((i + j) % 2 == 0){
                f.addEdge(s,p,1,0);
                f.addEdge(p,t,1,0);
            }else{
                f.addEdge(p,t,1,a[i][j]);
            }
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m -1;j++){
            int p =i * m + j, q = i * m + j + 1;
            if((i + j) % 2 == 1)swap(p,q);
            f.addEdge(p,q,1,a[p/m][p%m]);
        }
    }
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < m;j++){
            int p = i * m + j, q = i * m + j + m;
            if((i + j) % 2 == 1)swap(p,q);
            f.addEdge(p,q,1,a[p/m][p%m]);
        }
    }
    auto res = f.flow(s,t);
    //cerr<<res.first<<" "<<res.second;
    ll ans = sum - res.second;
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