#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<vector<pair<int,int>>>g(n);
    for(int i = 0;i < n-1;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }

    vector<ll>dp(n);
    vector<ll>val(n);
    for(int i = 0;i <n;i++){
        val[i] = a[i];
    }
    auto dfs = [&](auto &&self, int p, int fa)->void
    {
        for(auto [s,w] : g[p]){
            if(s != fa){
                self(self,s,p);
                val[p] += val[s];
                dp[p] += dp[s] + abs(val[s]) * w;
            }
        }
    };
    dfs(dfs,0,-1);
    cout<<dp[0]<<endl;
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