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
    vector<vector<int>>g(n);
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>cnt(n);
    cnt[0] = 1;
    queue<int>q;
    q.push(1);
    vector<int>vs(n);
    vector<int>dis(n, 19119810);
    while(!q.empty()){
        auto p = q.front();
        q.pop();
        if(vs[p])continue;
        vs[p] = 1;
        for(auto s : g[p]){
            if(!vs[s] && dis[s] >= dis[p] + 1){
                if(dis[s] == dis[p] + 1){
                    cnt[s] += cnt[p];
                    cnt[s] %= 100003;
                }
                else{
                    dis[s] = dis[p] + 1;
                    cnt[s] = cnt[p];
                }
            }
        }
    }

    for(int i = 0;i < n;i++){
        if(vs[i]){
            cout<<cnt[i]<<'\n';
        }
        else{
            cout<<0<<'\n';
        }
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