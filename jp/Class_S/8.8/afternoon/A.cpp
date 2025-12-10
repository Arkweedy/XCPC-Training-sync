#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,s;
    cin>>n>>m>>s;
    vector<vector<pair<int,int>>>g(n + 1);
    for(int i = 0;i < m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }

    //dij
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
    pq.push({0,s});
    constexpr ll inf = 1145141919810111;
    vector<ll>dis(n + 1, inf);
    vector<int>vs(n + 1);
    dis[s] = 0;

    while(!pq.empty()){
        auto [d, p] = pq.top();
        pq.pop();
        if(vs[p])continue;
        vs[p] = true;
        //dis[p] = d;
        for(auto [s, w] : g[p]){
            if(!vs[s] && dis[p] + w < dis[s]){
                dis[s] = dis[p] + w;
                pq.push({dis[s],s});
            }
        }
    }

    for(int i = 1;i <= n;i++){
        cout<<dis[i]<<" ";
    }
    cout<<endl;
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