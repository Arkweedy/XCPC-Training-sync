#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, m;
    cin>>n>>m;
    map<pair<int,int>,int>mp;
    int tot = n;
    vector<vector<pair<int,int>>>g(n);
    for(int i = 0;i < m;i++){
        int u,v,c;
        cin>>u>>v>>c;
        u--,v--;
        pair<int,int>pu = make_pair(u,c),pv = make_pair(v,c);
        if(!mp.count(pu)){
            mp[pu] = tot++;
            g.emplace_back();
        }
        if(!mp.count(pv)){
            mp[pv] = tot++;
            g.emplace_back();
        }
        int iu = mp[pu],iv = mp[pv];
        g[u].emplace_back(iu,1);
        g[v].emplace_back(iv,1);
        g[iu].emplace_back(u,1);
        g[iv].emplace_back(v,1);
        g[iu].emplace_back(iv,0);
        g[iv].emplace_back(iu,0);
    }

    //dij
    constexpr int inf = 1e9;
    vector<int>dis(tot,inf);
    vector<int>vs(tot);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;//dis , node
    pq.push({0,0});
    dis[0] = 0;
    while(!pq.empty()){
        auto [d, p] = pq.top();
        pq.pop();
        if(vs[p])continue;
        vs[p] = 1;
        dis[p] = d;
        for(auto [s, dd] : g[p]){
            if(!vs[s]){
                pq.push(make_pair(d + dd, s));
            }
        }
    }
    cout<<dis[n - 1] / 2<<endl;
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