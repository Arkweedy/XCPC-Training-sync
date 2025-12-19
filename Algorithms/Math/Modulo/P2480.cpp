#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;

using namespace std;

//P2480.cpp Create time : 2025.12.17 17:05


template<typename T>
T exgcd(T a, T b, T &x, T &y)
{
    x = 1, y = 0;
    array<T, 4>m = {1, 0, 0 ,1};//matrix
    while(b != 0){
        T c = a / b;
        m = {m[1], m[0] - c * m[1], m[3], m[2] - c * m[3]};
        T t = a % b;
        a = b;
        b = t;
    }
    x = m[0], y = m[2];
    return a;
}

ll inv(ll a, ll m)
{
    ll x, y;
    exgcd(a, m, x, y);
    if(x < 0)x += m;
    return x;
}

i64 crt(const vector<i64>&m, const vector<i64>&r)
{
    int n = m.size();
    i64 M = 1;
    for(int i = 0;i < n;i++){
        M *= m[i];
    }
    i128 ans = 0;
    for(int i = 0;i < n;i++){
        i128 c = inv(M / m[i], m[i]) * r[i] % M;
        ans = (ans + c * (M / m[i])) % M;
    }
    ans = (ans + M) % M;
    return ans;
}

// g^{\sum_{d | n} \binom{n}{d}} mod P
//calc \sum_{d | n} \binom{n}{d} mod P - 1
//using crt and lucas

//lucas : 
//\binom{n}{m} mod p = \binom{n / p}{m / p} * \binom{n % p}{m % p} mod p

//P-1 = 2 * 3 * 4679 * 35617

constexpr int PP = 999911659;
int power(int a, ll p)
{
    if(a == 0)return 0;//attension p is mod PP - 1, 0 ^ (k * (PP - 1)) = 0
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % PP;
        a = 1ll * a * a % PP;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n, g;
    cin >> n >> g;

    vector<int>factor;
    for(int i = 1;i * i <= n;i++){
        if(n % i == 0){
            factor.push_back(i);
            if(i * i != n)factor.push_back(n / i);
        }
    }

    vector<ll>p = {2,3,4679,35617};
    vector<ll>r(4);
    for(int i = 0;i < 4;i++){
        const int P = p[i];
        vector<int>fac(P),invfac(P);
        fac[0] = invfac[0] = 1;
        for(int i = 1;i < P;i++){
            fac[i] = 1ll * fac[i - 1] * i % P;
        }
        invfac[P - 1] = P - 1;//Wilson 
        for(int i = P - 2;i >= 1;i--){
            invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
        }
        
        auto lucas = [&](this auto&& lucas, int n, int m)->int
        {
            if(m == 0)return 1;
            if(m > n)return 0;
            if(m < P && n < P)return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
            else return 1ll * lucas(n / P,m / P) * lucas(n % P, m % P) % P;
        };

        int res = 0;
        for(auto d : factor){
            res = (res + lucas(n, d)) % P;
        }
        r[i] = res;
    }

    ll ans = crt(p, r);
    ans = power(g % PP, ans);

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