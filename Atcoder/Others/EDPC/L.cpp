#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.15 22:02:08

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    constexpr i64 inf = 1e18;
    vector<vector<i64>>dp(n + 1, vector<i64>(n + 1));
    for(int k = n - 1;k >= 0;k--){
        if(k % 2 == 0){// 0 -> 1, Taro
            for(int j = 0;j <= k;j++){
                dp[k - j][j] = max(dp[k - j + 1][j] + a[k - j], dp[k - j][j + 1] + a[n - j - 1]);
            }
        }
        else{// min X - Y
            for(int j = 0;j <= k;j++){  
                dp[k - j][j] = min(dp[k - j + 1][j] - a[k - j], dp[k - j][j + 1] - a[n - j - 1]);          
            }
        }
    }
    // for(int i = 0;i <= n;i++){
    //     for(int j = 0;j <= n;j++){
    //         cerr << dp[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;
    i64 ans = dp[0][0];
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