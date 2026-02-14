#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.12 20:52

constexpr int P = 998244353;

int power(int a, int p)
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
    int n, k, d;
    cin >> n >> k >> d;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>fac(n + 1),invfac(n + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = power(fac[n], P - 2);
    for(int i = n - 1;i >= 1;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    auto f = [&](int n, int k)->int // \binom{n - k + 1}{k}
    {
        if(k > n - k + 1 || k < 0)return 0;
        return 1ll * fac[n - k + 1] * invfac[k] % P * invfac[n - k * 2 + 1] % P;
    };

    //ox
    //xox
    //oxoxox
    //|oxoxo| // mid

    vector<int>c(n);
    c[0] = c[n - 1] = f(n - 2, k - 1);
    if(n > 2){
        c[1] = c[n - 2] = f(n - 3, k - 1);
        for(int i = 2;i < (n + 1) / 2;i++){
            if(i % 2 == 1)c[i] = (c[i - 2] + f(n - i * 2 - 1, k - i / 2 * 2 - 1)) % P;
            else c[i] = (c[i - 1] + f(n - i / 2 * 4 - (i * 2 + 1 == n ? 1 : 2), k - i / 2 * 2 - 1)) % P;
            c[n - i - 1] = c[i];
        }
    }

    i64 ans = 0;
    for(int i = 0;i < n;i++){
        //cerr << c[i] << " ";
        ans += 1ll * a[i] * c[i] % P;
    }
    ans %= P;
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