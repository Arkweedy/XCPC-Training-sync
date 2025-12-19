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

i64 crt(const array<i64, 4>&m, const array<i64, 4>&r)
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

template<int P>
long long calc_sum(int n, const vector<int>& factor) {
    static array<int, P> fac, ifac;
    static bool inited = false;
    if (!inited) {
        fac[0] = 1;
        for (int i = 1; i < P; i++) fac[i] = 1LL * fac[i-1] * i % P;
        ifac[P-1] = P - 1;                 // Wilson
        for (int i = P-2; i >= 1; i--) ifac[i] = 1LL * ifac[i+1] * (i+1) % P;
        ifac[0] = 1;
        inited = true;
    }

    auto Csmall = [&](int nn, int kk)->int{
        if (kk < 0 || kk > nn) return 0;
        return 1LL * fac[nn] * ifac[kk] % P * ifac[nn-kk] % P;
    };

    auto lucas = [&](auto&& self, int nn, int kk)->int {
        if (kk == 0) return 1;
        if (kk > nn) return 0;
        if (nn < P && kk < P) return Csmall(nn, kk);
        return 1LL * self(self, nn / P, kk / P) * Csmall(nn % P, kk % P) % P;
    };

    long long res = 0;
    for (int d : factor) res = (res + lucas(lucas, n, d)) % P;
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

    constexpr array<long long,4> p = {2,3,4679,35617};
    array<long long,4> r;
    r[0] = calc_sum<2>(n, factor);
    r[1] = calc_sum<3>(n, factor);
    r[2] = calc_sum<4679>(n, factor);
    r[3] = calc_sum<35617>(n, factor);

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