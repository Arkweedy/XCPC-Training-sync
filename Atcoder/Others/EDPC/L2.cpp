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
        for(int j = 0;j <= k;j++){
            dp[k - j][j] = max(a[k - j] - dp[k - j + 1][j] , a[n - j - 1] - dp[k - j][j + 1]);
        }
    }
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