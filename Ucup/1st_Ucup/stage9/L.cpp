#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.28 12:12:43
constexpr int P = 1e9 + 7;

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

void solve()
{
    i64 n, m;
    cin >> n >> m;
    if(m > n){
        cout << 0 << endl;
        return;
    }
    vector<int>fac(n + 1), invfac(n + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = power(fac[n], P - 2);
    for(int i = n - 1;i >= 1;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    if(m == n){
        cout << 1ll * fac[n - 1] * invfac[2] % P << "\n";
        return;
    }

    auto binom = [&](int n, int m)->int
    {
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };
    i64 k = n - m;

    auto A = [&](int i)->int
    {
        return binom(k + i - 1, i);
    };
   
    i64 ans = 0;
    int k2 = power(2, k);
    int i2 = (P + 1) / 2;
    for(int i = 0;i <= min(n - k, k);i++){
        ans = (ans + 1ll * binom(k, i) * k2 % P * (i % 2 == 0 ? 1 : P - 1) % P * A(n - k - i)) % P;
        k2 = 1ll * k2 * i2 % P;
    }
    ans = 1ll * ans * power(power(2, k), P - 2) % P;
    ans = 1ll * ans * fac[n] % P;
    ans = 1ll * ans * invfac[k] % P;
    cout << ans << "\n";
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}