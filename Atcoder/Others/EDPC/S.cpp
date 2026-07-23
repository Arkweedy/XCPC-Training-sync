#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.16 14:32:09

constexpr int P = 1e9 + 7;

void solve()
{
    string s;
    int d;
    cin >> s >> d; 
    int n = s.length();
    //1e4, not use

    vector<vector<int>>dp(n + 1, vector<int>(d));
    dp[0][0] = 1;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= 9;j++){
            for(int k = 0;k < d;k++){
                dp[i][(k + j) % d] = (dp[i][(k + j) % d] + dp[i - 1][k]) % P;
            }
        }
    }

    i64 ans = 0;
    [&](this auto&&dfs, int p, int lead)->void
    {
        if(p == n){
            if(lead == 0)ans++;
            return;
        }
        int x = s[p] - '0', y = n - p - 1;
        for(int i = 0;i < x;i++){
            ans += dp[y][(2 * d - i - lead) % d];
            ans %= P;
        }
        lead += x;
        lead %= d;
        dfs(p + 1, lead);
    }(0, 0);
    ans--; // 0
    ans = (ans + P) % P;
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