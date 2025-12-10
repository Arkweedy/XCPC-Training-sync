#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 998244353;

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<ll>>dp(n,vector<ll>(1,1));
    //vector<int>sz(n, 1);
    //cerr<<"ok"<<endl;
    
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        int isleaf = 1;
        for(auto s : g[p]){
            if(s != fa){
                isleaf = 0;
                self(self,s ,p);
                int x = dp[p].size(), y = dp[s].size();
                vector<ll>ndp(x + y - 1);
                for(int i = 0;i < x;i++){
                    for(int j = 0;j < y;j++){
                        ndp[i + j] = (ndp[i + j] +  dp[p][i] * dp[s][j]) % P;
                    }
                }
                dp[p] = move(ndp);
            }
        }
        //if(isleaf)dp[p][0] = 1;
        vector<ll>ndp(dp[p].size() + 1);
        for(int i = 0;i < dp[p].size();i++){
            if(i != a[p]){
                ndp[i] = (ndp[i] + dp[p][i]) % P;
            }
            if(i == a[p] - 1){
                ndp[i + 1] = (ndp[i + 1] + dp[p][i]) % P;
            }
        }
        dp[p] = ndp;
        
        return;
    };
    dfs(dfs,0,-1);
    

    ll ans = 0;
    for(int i = 0;i <= n;i++){
        ans = (ans + dp[0][i]) % P;
    }
    cout<<ans<<endl;
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