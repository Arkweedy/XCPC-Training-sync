#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.05.16 03:18

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    constexpr int inf = 2e9;
    vector<int>dp(n, inf);
    dp[0] = 0;
    for(int i = 1;i < n;i++){
        dp[i] = min(dp[i], dp[i - 1] + abs(a[i] - a[i - 1]));
        if(i > 1)dp[i] = min(dp[i], dp[i - 2] + abs(a[i] - a[i - 2]));
    }
    cout << dp[n - 1] << endl;
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