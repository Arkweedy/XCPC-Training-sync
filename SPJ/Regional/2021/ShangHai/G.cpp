#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

constexpr int P = 998244353;

void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>dp(n, 1),sz(n, 1);

    vector<int>dfac(n + 1);
    dfac[0] = dfac[1] = 1;
    for(int i = 2;i <= n;i++){
        dfac[i] = 1ll * dfac[i - 2] * i % P;
    }

    
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        int x = 0;
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                sz[p] += sz[s];
                dp[p] = 1ll * dp[p] * dp[s] % P;
                if(sz[s] % 2 == 1)x++;//odd edge
            }
        }
        if(x % 2 == 1)x++;
        
        if(x > 0)dp[p] = 1ll * dp[p] * dfac[x - 1] % P;
        return;
    };

    

    dfs(dfs, 0, -1);

    cout<<dp[0]<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}