#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.08 15:13:23

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

int inv(int a)
{
    return power(a, P - 2);
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>fac(n + 1), invfac(n + 1), Inv(n + 1);
    fac[0] = 1;
    for(int i = 1;i <= n; i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = inv(fac[n]);
    for(int i = n - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
        Inv[i + 1] = 1ll * invfac[i + 1] * fac[i] % P;
    }

    if(n <= k){
        cout << fac[n] << endl;
        return;
    }

    vector<int>f(n + 1, 1);
    for(int i = k + 1;i <= n;i++){
        f[i] = (f[i - 1] - 1ll * Inv[i] * f[i - k - 1] % P + P) % P;
    }
    int ans = 1ll * f[n] * fac[n] % P;
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