#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll l,r;
    cin>>l>>r;
    auto calc = [&](ll r)->ll
    {
        ll res = 0;
        res += r / 2;
        res += r / 3;
        res += r / 5;
        res += r / 7;
        res -= r / 6;
        res -= r / 10;
        res -= r / 14;
        res -= r / 15;
        res -= r / 21;
        res -= r / 35;
        res += r / 30;
        res += r / 42;
        res += r / 70;
        res += r / 105;
        res -= r / 210;
        return res;
    };
    cout<<r - l + 1 - (calc(r) - calc(l - 1))<<endl;
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