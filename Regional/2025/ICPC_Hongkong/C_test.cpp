#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.29 16:56:18

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

constexpr int N = 1e7 + 10;

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    i64 s = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        s += a[i];
    }

    vector<int> fac(N + 1),invfac(N + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[N] = power(fac[N], P - 2);
    for(int i = N - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    i64 ans = 0;
    i64 cs = 1;
    for(int i = 0;i < n;i++){
        cs = cs * ((n + s - i) % P) % P;
    }
    cs = cs * invfac[n] % P;

    ans += cs;

    auto binom = [&](int n, int m)->int
    {
        if(n < m || m < 0 || n < 0)return 0;
        return 1ll * fac[n] * invfac[n - m] % P * invfac[m] % P;
    };

    i64 res1 = 0;
    for(int i = 0;i < n;i++){
        if(s - i <= n * (n - i - 1)){
            //cerr << "in, i = " << i << endl;
            int k = (s - i) / (n - i);
            i64 ss = 0;
            //cerr << k << endl;
            for(int j = 0;j <= k;j++){
                i64 x = (j % 2 == 0 ? 1 : P-1);
                x = x * binom(n, j) % P;
                x = x * binom(n + s - i - j * (n - i) - 1, n - 1) % P;
                ss = (ss + x + P) % P;
                //cerr << x << endl;
            }
            //cerr << ss << endl;
            res1 += ss;
        }
    }
    ans -= res1;
    ans = (ans % P + P) % P;

    int ill = 1;
    for(int i = 0;i < n;i++){
        if(a[i] >= n){
            ill = 0;
        }
    }
    if(ill){
        vector<int>f(n + 1);
        f[0] = 1;
        auto mul = [&](int k)->void
        {
            for(int i = n;i >= k;i--){
                f[i] = (f[i] - f[i - k] + P) % P;
            }
        };
        auto div = [&](int k)->void
        {
            for(int i = k;i <= n;i++){
                f[i] = (f[i] + f[i - k]) % P;
            }
        };
        auto Mul = [&](int k)->void
        {
            div(1);
            mul(k + 1);
        };
        auto Div = [&](int k)->void
        {
            div(k + 1);
            mul(1);
        };
        auto Upt = [&](int k)->void
        {
            div(k + 1);
            mul(k);
        };

        for(int i = 0;i < n;i++){
            Mul(a[i]);
        }

        int use = 0;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(a[j] == n - i){
                    Upt(a[j]);
                    a[j]--;
                    use++;
                    if(use > i)goto out;
                }
            }
            ans = (ans + f[i - use]) % P;
        }
        out:
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