#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//ARC107D.cpp Create time : 2026.09.26 19:26

constexpr int P = 998244353;

//f(n, k) = f(n - 1, k - 1) + f(n, k * 2)

void solve()
{
    int n, k;
    cin >> n >> k;
    
    vector<vector<int>>dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = i;j >= 1;j--){
            dp[i][j] += dp[i - 1][j - 1];
            if(j * 2 <= n)dp[i][j] += dp[i][j * 2];
            if(dp[i][j] >= P)dp[i][j] -= P;
        }
    }
    cout << dp[n][k] << endl;
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