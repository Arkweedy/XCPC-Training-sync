#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.15 15:50
constexpr int P = 998244353;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n + 1);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
    }
    vector<vector<i64>>sum(n + 1, vector<i64>(k + 1));//end is i, k times
    vector<vector<i64>>dp(n, vector<i64>(k + 1));
    dp[0][0] = 2;
    sum[a[0]][0] = 1;
    sum[n][0] = 1;
    for(int i = 1;i < n;i++){
        dp[i] = dp[i - 1];//0
        vector<i64>ndp(k + 1);
        ndp[0] = (dp[i - 1][0] - sum[a[i]][0] + P) % P;
        for(int j = 1;j <= k;j++){
            ndp[j] = (1ll * sum[a[i]][j - 1] + dp[i - 1][j] - sum[a[i]][j] + P) % P;
        }
        for(int j = 0;j <= k;j++){
            dp[i][j] = (dp[i][j] + ndp[j]) % P;
        }
        //1
        for(int j = 0;j <= k;j++){
            sum[a[i]][j] = (sum[a[i]][j] + ndp[j]) % P;
        }
    }

    int ans = dp[n - 1][k];
    cout << ans << endl;
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