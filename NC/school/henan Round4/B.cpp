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
    auto get = [&](ll n, int p)->ll
    {
        ll res = 0;
        for(ll x = p;x <= n;x *= p){
            res += n / x;
        }
        return res;
    };
    auto calc = [&](ll n, int p)->ll
    {
        ll res = 0;
        for(ll l = 1, r;l <= n;l = r + 1){
            r = n / (n / l);
            res += (n / l) * (get(r, p) - get(l - 1, p));
        }
        return res;
    };

    cout<<min(calc(r,2)-calc(l-1,2), calc(r,5)-calc(l-1,5))<<endl;
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