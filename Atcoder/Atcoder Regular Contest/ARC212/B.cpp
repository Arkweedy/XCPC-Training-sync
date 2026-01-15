#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//B.cpp Create time : 2026.01.11 20:26

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>>g(n);
    int s, t;
    cin >> s >> t;
    s--,t--;
    //t += n;
    i64 ans;
    cin >> ans;
    for(int i = 1;i < m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        //cerr << u << " " << v << " " << w << endl;
        u--,v--;
        swap(u, v);
        g[u].emplace_back(v, w);
        //g[v].emplace_back(u, w);
    }

    priority_queue<pair<i64,int>,vector<pair<i64,int>>,greater<>>pq;
    vector<i64>dis(n, -1);
    pq.push({0, s});

    while(!pq.empty()){
        auto [d, p] = pq.top();
        pq.pop();
        if(dis[p] != -1)continue;
        dis[p] = d;
        for(auto [s, x] : g[p]){
            if(dis[s] == -1){
                pq.emplace(d + x, s);
            }
        }
    }

    if(dis[t] == -1){
        cout << -1 << endl;
    }
    else{
        ans += dis[t];
        cout << ans << endl;
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