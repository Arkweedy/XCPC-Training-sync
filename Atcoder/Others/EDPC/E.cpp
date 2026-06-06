#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.05.27 13:15

void solve()
{
    int n, m;
    cin >> n >> m;
    const int N = n * 1000;
    constexpr i64 inf = 1e13;
    vector<i64>dp(N + 1, inf);
    dp[0] = 0;
    for(int i = 0;i < n;i++){
        int v, w;
        cin >> w >> v;
        for(int j = N;j >= v;j--){
            dp[j] = min(dp[j], dp[j - v] + w);
        }
    }
    i64 ans = 0;
    for(int i = 0;i <= N;i++){
        if(dp[i] <= m)ans = i;
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