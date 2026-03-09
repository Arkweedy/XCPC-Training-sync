#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1736E.cpp Create time : 2026.02.28 15:01

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    constexpr int inf = 1e9;
    vector<vector<int>>dp(n + 1, vector<int>(n + 1, -inf));
    dp[0][0] = 0;
    // dp[j][k]
    for(int i = 1;i <= n;i++){
        vector<vector<int>>ndp(n + 1, vector<int>(n + 1, -inf));
        vector<vector<int>>pma(n + 1, vector<int>(n + 1, -inf));
        if(i > 1){
            for(int j = 1;j <= n;j++){
                for(int k = 1;k <= i;k++){
                    ndp[j][k] = dp[j][k - 1] + a[j];
                }
            }
        }
        pma[0] = vector<int>(n + 1, 0);
        for(int t = 1;t <= n;t++){
            for(int k = 0;k <= i - 1;k++){
                pma[t][k] = max(pma[t - 1][k], dp[t][k]);
            }
        }
        for(int j = i;j <= n;j++){
            for(int k = 0;k <= i;k++){
                if(k - (j - i) >= 0)ndp[j][k] = max(ndp[j][k], pma[j - 1][k - (j - i)] + a[j]);
            }
        }
        dp = move(ndp);
    }

    int ans = 0;
    for(int j = 1;j <= n;j++){
        for(int k = 0;k <= n;k++){
            ans = max(ans, dp[j][k]);
        }
    }
    cout << ans << endl;
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