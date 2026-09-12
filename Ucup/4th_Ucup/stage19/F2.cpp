#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F2.cpp Create time : 2026.09.11 18:40

constexpr int P = 998244353;
int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int inv(int a)
{
    return power(a, P - 2);
}

void solve()
{
    int n, l;
    cin >> l >> n;
    const int N = l * 2 + 1;
    vector<int>fac(N + 1), invfac(N + 1);
    fac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[N] = inv(fac[N]);
    for(int i = N - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    auto binom = [&](int n, int m)->int
    {
        if(n < 0 || m < 0 || n < m)return 0;
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };

    auto f = [&](int n, int t, int m)->int // n beats to t seg, max leq m
    {
        int res = 0;
        if(n < t)return 0;
        n -= t;
        for(int i = 0;i <= min(n / m, t);i++){
            int x = ((i % 2 == 0 ? 1 : -1) * binom(t, i) + P) % P;
            res = (res + 1ll * x * binom(t + n - i * m - 1, n - i * m)) % P;
        }
        return res;
    };

    vector<int>g(l + 1);
    for(int i = 1;i <= l;i++){
        g[i] = f(l, n, i);
    }
    for(int i = l;i >= 1;i--){
        g[i] = (g[i] - g[i - 1] + P) % P;
    }
    int ans = 0;
    for(int i = 1;i <= l;i++){
        ans = (ans + 1ll * i * g[i]) % P;
    }
    ans = 1ll * ans * l % P * inv(n) % P;
    ans = 1ll * ans * inv(binom(l, n)) % P;
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