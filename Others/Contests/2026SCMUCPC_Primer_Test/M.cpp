#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//M.cpp Create time : 2026.05.09 21:10

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

int n, k, r;
map<int,int>mp;

auto g(int n)->int // \sum_0 k^i
{
    if(n == 0)return 1;
    if(mp.count(n))return mp[n];
    if(n % 2 == 0){
        return (g(n - 1) + power(k, n)) % P;
    }
    else{
        return mp[n] = (1ll * (power(k, n / 2 + 1) + 1) * g(n / 2)) % P;
    }
};

auto f(int n)->int // \sum_0 k^i (i + 1)
{
    if(n == 0)return 1;
    if(n % 2 == 0){
        return (1ll * power(k, n) * (n + 1) + f(n - 1)) % P;
    }
    else{
        int i = n / 2 + 1;
        int pk = power(k, i);
        return (1ll * (pk + 1) * f(i - 1) + 1ll * i * pk % P * g(i - 1)) % P;
    }
};

void solve()
{
    mp.clear();
    cin >> n >> k >> r;
    //n = 1e9, k = 1e9, r = 1e9;
    i64 res = (1ll * r * power(k, n) + f(n - 1)) % P;
    cout << res << "\n";
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