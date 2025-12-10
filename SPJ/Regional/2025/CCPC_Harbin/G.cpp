#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr ll inf = 1e18;

void solve()
{
    int n,m;cin>>n>>m;
    vector<vector<ll>>h(n,vector<ll>(m));
        ll res = 0,sum = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)cin>>h[i][j],sum += h[i][j];
        for(int j=1;j<m;j++)h[i][j] += h[i][j-1];
    }
    vector<vector<ll>>dp(n,vector<ll>(m));
    

    for(int j=0;j<m;j++){
        dp[0][j] = h[0][j];
    }

    for(int i=1;i<n;i++){
        for(int j=m-1;j>=0;j--){
            dp[i][j] = dp[i-1][j];
            if(j+1<m)dp[i][j] = min(dp[i][j],dp[i][j+1]);
        }
        res = min(res,dp[i][0]);
        for(int j=0;j<m;j++)dp[i][j] += h[i][j];
    }

    
    for(int j=0;j<m;j++){
        res = min(res,dp[n-1][j]);
        
    }
    

    cout<<max(0ll,-2 * res + sum)<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}