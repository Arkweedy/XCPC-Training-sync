#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1515E_Fast.cpp Create time : 2026.10.01 19:01

int power(int a, int p, int P)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * a * res % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n, P;
    cin >> n >> P;

    vector<vector<int>>dp(n + 1, vector<int>(n + 1));
    // dp[i][j] -> insert i-th , has j component
    // i + j - 1 <= n
    dp[0][0] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 1;i + j - 1 <= n;j++){
            dp[i][j] = (1ll * dp[i - 1][j - 1] * j + 1ll * dp[i - 1][j] * j * 2) % P;
        }
    }

    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans = (ans + dp[i][n - i + 1]) % P;
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