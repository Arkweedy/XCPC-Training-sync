#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

pair<ll,ll>simigcd(ll a,ll b,ll c,ll d)
{
    if(a < b && c > d){
        return {1,1};
    }else if(a >= b && c >= d){
        ll k = a / b;
        auto res = simigcd(a - k * b, b, c - k * d, d);
        res.first += res.second * k;
        return res;
    }else{
        auto res = simigcd(d, c, b, a);
        swap(res.first,res.second);
        return res;
    }
}

pair<ll,ll>Simigcd(ll a,ll b,ll c,ll d)
{
    if(a < b && c > d){
        return {1,1};
    }else{
        ll k = d / c;
        auto res = Simigcd(d % c, c, b - a * k, a);
        res.first += res.second * k;
        swap(res.first,res.second);
        return res;
    };
}

void solve()
{
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    auto res = simigcd(a,b,c,d);
    cout<<res.second<<endl;
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