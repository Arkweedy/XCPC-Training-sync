#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1515E.cpp Create time : 2026.10.01 12:34

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
    vector<int>fac(n + 1), invfac(n + 1);
    fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = power(fac[n], P - 2, P);
    for(int i = n - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    auto binom = [&](int n, int m)->int
    { 
        if(n < 0 || m < 0 || n < m)return 0;
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };

    vector<int>p2(n + 1);
    p2[0] = 1;
    for(int i = 1;i <= n;i++){
        p2[i] = p2[i - 1] * 2 % P;
    }

    vector<vector<int>>dp(n + 2, vector<int>(n + 1));
    dp[0][0] = 1;
    for(int i = 1;i <= n + 1;i++){
        for(int j = 0;j < i - 1;j++){
            int c = i - j - 1;
            for(int k = 0;k <= j;k++){
                dp[i][k + c] = (dp[i][k + c] + 1ll * dp[j][k] * p2[c - 1] % P * binom(k + c, c)) % P;
            }
        }
    }

    int ans = 0;
    for(int i = 1;i <= n;i++){
        ans = (ans + dp[n + 1][i]) % P;
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