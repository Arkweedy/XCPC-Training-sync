#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.05.16 03:32

void solve()
{
    int n;
    cin >> n;
    vector<array<int,3>>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }
    vector<array<int,3>>dp(n);
    dp[0][0] = a[0][0];
    dp[0][1] = a[0][1];
    dp[0][2] = a[0][2];
    for(int i = 1;i < n;i++){
        dp[i][0] = max(dp[i - 1][1] + a[i][0], dp[i - 1][2] + a[i][0]);
        dp[i][1] = max(dp[i - 1][0] + a[i][1], dp[i - 1][2] + a[i][1]);
        dp[i][2] = max(dp[i - 1][0] + a[i][2], dp[i - 1][1] + a[i][2]);
    }
    int ans = max(max(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
    cout << ans << endl;
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