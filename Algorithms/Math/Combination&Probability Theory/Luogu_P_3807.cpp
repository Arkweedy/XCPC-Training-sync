#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int power(int a, int p, int mod)
{
    a %= mod;
    p %= (mod - 1);
    int res = 1;
    while(p != 0){
        if(p & 1){
            res = 1ll * res * a % mod;
        }
        a = 1ll * a * a % mod;
        p>>=1;
    }
    return res;
}

int inv(int a, int mod)
{
    return power(a, mod-2, mod);
}

void solve()
{
    int n, m, p;
    cin>>n>>m>>p;
    vector<int>fac(p + 1),invfac(p + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= p;i++){
        fac[i] = 1ll * fac[i - 1] * i % p;
    }

    invfac[p - 1] = inv(fac[p - 1], p);
    for(int i = p - 2;i >= 1;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % p;
    }


    auto binom = [&](int n, int m)->int
    {
        if(n < m)return 0;
        else return 1ll * fac[n] * invfac[m] % p * invfac[n - m] % p;
    };

    auto Lucas = [&](auto&&self, int n, int m)->int
    {
        if(n >= p || m >= p){
            return 1ll * self(self, n / p, m / p) * binom(n % p, m % p) % p; 
        }
        else{
            return binom(n, m);
        }
    };

    cout<<Lucas(Lucas,n + m,m)<<endl;
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