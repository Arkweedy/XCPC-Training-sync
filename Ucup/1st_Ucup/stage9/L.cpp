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
    vector<int>fac(n * 2 + 1), invfac(n * 2 + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= n * 2;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n * 2] = power(fac[n], P - 2);
    for(int i = n * 2 - 1;i >= 1;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    auto binom = [&](int n, int m)->int
    {
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };

    vector<int>f{1};
    auto add = [&]()->void
    {
        int m = f.size();
        f.resize(m + 2);
        for(int i = m + 1;i >= 0;i--){
            i64 v = 0;
            if(i > 0)v += 2 * f[i - 1];
            if(i > 1)v -= f[i - 2];
            v = (v % P + P) % P;
            f[i] = v;
        }
        // for(auto x : f){
        //     cerr << x << " ";
        // }
        // cerr << endl;
        return;
    };

    int k = n - m;
    for(int i = 0;i < k;i++){
        add();
    }
    i64 ans = 0;
    f.resize(n + 1);
    for(int i = 0;i <= n;i++){
        ans = (ans + 1ll * binom(k + i - 1, i) * f[n - i]) % P;
    }
    ans = 1ll * ans * power(power(2, k), P - 2);
    ans = 1ll * ans * fac[n] % P;
    
    cout << ans << endl;
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