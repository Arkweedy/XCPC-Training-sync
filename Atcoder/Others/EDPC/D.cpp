#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.05.27 01:06

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64>dp(m + 1);
    vector<int>w(n),v(n);
    for(int i = 0;i < n;i++){
        cin >> w[i] >> v[i];
    }
    for(int i = 0;i < n;i++){
        for(int j = m;j >= w[i];j--){
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    i64 ans = 0;
    for(int i = 0;i <= m;i++){
        ans = max(ans, dp[i]);
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