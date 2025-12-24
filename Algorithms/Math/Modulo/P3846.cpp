#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//P3846.cpp Create time : 2025.12.22 00:48



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

int bsgs(int a, int b, int p)
{
    a %= p;
    b %= p;
    if(p == 1) return 0;
    if(b == 1) return 0;

    int sq = ceil(sqrt(p));

    unordered_map<int,int>mp;
    int x = 1;
    for(int i = 0;i <= sq;i++){
        mp[1ll * x * b % p] = i;
        x = 1ll * x * a % p;
    }

    int asq = power(a, sq, p);
    int y = asq;
    for(int i = 1;i <= sq;i++){
        if(mp.find(y) != mp.end()){
            return i * sq - mp[y];
        }
        y = 1ll * y * asq % p;
    }
    return -1;
}

void solve()
{
    int n, b, p;
    cin >> p >> b >> n;
    int res = bsgs(b, n, p);
    if(res == -1)cout << "no solution" << endl;
    else cout << res << endl;
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