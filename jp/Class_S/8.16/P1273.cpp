#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>g(n + 1);
    vector<int>val(n + 1);
    for(int i = 1;i <= n - m;i++){
        int k;
        cin>>k;
        for(int j = 0;j < k;j++){
            int a, c;
            cin>>a>>c;
            g[i].push_back(a);
            val[a] -= c;
        }
    }

    for(int i = n - m + 1;i <= n;i++){
        int v;
        cin>>v;
        val[i] += v;
    }

    constexpr int inf = 1145141919;
    vector<vector<int>>dp(n + 1,vector<int>(m + 1, -inf));
    vector<int>sz(n + 1);
    for(int i = 1;i <= n;i++){
        if(i <= n - m)dp[i][0] = val[i];
        else{
            dp[i][0] = 0;
            dp[i][1] = val[i];
        }
    }
    for(int i = n - m + 1;i <= n;i++){
        sz[i] = 1;
    }

    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            self(self, s);
            sz[p] += sz[s];
            //dp[p][i + j] = max(dp[p][i + j], dp[p][i] + dp[s][j])
            for(int i = sz[p];i >= 0;i--){
                for(int j = 0;j + i <= sz[p] && j <= sz[s];j++){
                    dp[p][i + j] = max(dp[p][i + j], dp[p][i] + dp[s][j]);
                }
            }
        }
        // if(p <= n - m){//
        //     for(int i = 1;i <= sz[p];i++){
        //         dp[p][i] += val[p];
        //     }
        // }
        // else{
        //     dp[p][1] = val[p];
        // }
    };

    dfs(dfs, 1);
    int ans = -1;
    for(int i = 0;i <= m;i++){
        if(dp[1][i] >= 0){
            ans = i;
        }
    }

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