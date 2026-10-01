#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//603B.cpp Create time : 2026.09.26 08:04

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

int power(int a, int p, int P)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

vector<i64> factorize(i64 n) // or Miller-Rabin + Pollard Rho
{
    vector<i64>res;
    for(i64 i = 2;i * i <= n;i++){
        while(n % i == 0){
            res.push_back(i);
            n /= i;
        }
    }
    if(n != 1)res.push_back(n);
    return res;
}

i64 phi(i64 n)
{
    auto facs = factorize(n);
    i64 phi = 1;
    for(int i = 0;i < facs.size();i++){
        if(i == 0 || facs[i] != facs[i - 1])phi *= (facs[i] - 1);
        else phi *= facs[i];
    }
    return phi;
}

i64 ord(i64 n, i64 k)
{
    k %= n;
    if(gcd(n, k) != 1)return 0;

    i64 s = phi(n);
    auto pfacs = factorize(s);
    for(auto q : pfacs){
        while(s % q == 0 && power(k, s / q, n) == 1){
            s /= q;
        }
    }

    return s;
}

void solve()
{
    int p, k;
    cin >> p >> k;
    if(k == 0){
        cout << power(p, p - 1) << endl;
        return;
    }
    else if(k == 1){
        cout << power(p, p) << endl;
        return;
    }
    
    int s = ord(p, k);
    
    int c = (p - 1) / s;
    int ans = power(p, c);
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