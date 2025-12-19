#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t; 

using namespace std;

//P1495.cpp Create time : 2025.12.17 16:29

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

void solve()
{
    ll n;
    cin >> n;
    vector<ll>p(n),r(n);
    for(int i = 0;i < n;i++){
        cin >> p[i] >> r[i];
    }
    i64 ans = crt(p,r);
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