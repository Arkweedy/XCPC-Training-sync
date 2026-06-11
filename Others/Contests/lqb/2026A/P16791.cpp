#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.11 18:32:07

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
    int n;
    cin >> n;
    vector<int>fac(n + 1), d(n + 1), invfac(n + 1);
    fac[0] = 1;
    d[0] = 1;
    d[1] = 0;
    
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
        if(i >= 2)d[i] = 1ll * (i - 1) * (d[i - 1] + d[i - 2]) % P;
    }
    invfac[n] = power(fac[n], P - 2);
    for(int i = n - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }
 
    auto binom = [&](int n, int m)->int
    {
        if(n < 0 || m < 0 || m > n)return 0;
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };

    int ans = 0;
    for(int i = 0;i <= n / 2;i++){
        ans = (ans + 1ll * binom(n, i) * d[i]) % P;
    }
    cout << ans << endl;
    return;

    // iota(a.begin(),a.end(), 0);
    // int ans = 0;
    // do{
    //     int c = 0;
    //     for(int i = 0;i < n;i++){
    //         int cnt = 0;
    //         for(int j = 0;j < n;j++){
    //             if(j < i && a[j] < a[i]){
    //                 cnt++;
    //             }
    //             if(i < j && a[i] < a[j]){
    //                 cnt--;
    //             }
    //         }
    //         if(cnt == 0)c++;
    //     }
    //     if(c >= (n + 1) / 2){
    //         for(int i = 0;i < n;i++){
    //             cerr << a[i] << " ";
    //         }
    //         cerr << "cnt = " << c << endl;
    //         ans++;
    //     }
    // }while(next_permutation(a.begin(),a.end()));
    cout << ans << endl;
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