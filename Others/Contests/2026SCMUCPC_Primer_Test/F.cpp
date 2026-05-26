#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.05.09 19:23

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

void solve()
{
    int n;
    cin >> n;
    map<int,int>mp;
    for(int i = 0;i < n;i++){
        string s;
        cin >> s;
        mp[s.length()]++;
    }

    // vector<int>fac(n + 1), invfac(n + 1);
    // fac[0] = 1;
    // for(int i = 1;i <= n;i++){
    //     fac[i] = 1ll * fac[i - 1] * i % P;
    // }
    // invfac[n] = power(fac[n], P - 2);
    // for(int i = n - 1;i >= 0;i--){
    //     invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    // }

    auto A = [&](int n, int m)->int // use \frac{n^{\underline{m}}}{m!}
    {
        if(n < m)return 0;
        int res = 1;
        for(int i = 0;i < m;i++){
            res = 1ll * res * (n - i) % P;
        }
        return res;
    };

    i64 ans = 1;
    int flg = 1;
    //
    for(auto [l, c] : mp){
        if(l <= 6){
            int ac = power(26, l);
            if(ac < c){
                ans = 0;
                flg = 0;
            }
            else{
                ans = ans * A(ac, c) % P;
            }
        }
        else{ 
            //C(n, m) = C(n / P, m / P) * C(n % P, m % P)  // m / P = 0
            //        = C(n % P, m % P)
            ans = ans * A(power(26, l), c) % P;
        }
    }
    cout << (flg ? "YES" : "NO") << endl;
    //cout << ans << endl;
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