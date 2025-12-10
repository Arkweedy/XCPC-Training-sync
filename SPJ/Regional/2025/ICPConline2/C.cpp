#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1e5 + 10;

void solve()
{
    ll S;cin>>S;
    ll x1,x2,x12,x3,x23,x13,x123;
    cin>>x3>>x13>>x23>>x123;
    auto check = [&](ll k)->bool{
        ll a1 = max(k-x1,0ll);
        ll a2 = max(k-x2,0ll);
        ll a3 = max(k-x3,0ll);
        if(a1 > x12 + x13 + x123)return 0;
        if(a2 > x12 + x23 + x123)return 0;
        if(a3 > x13 + x23 + x123)return 0;
        if(a1+a2+a3 > x12 + x13 + x23 + x123)return 0;
        return 1;
    };
    
    ll l = 0,r = 1e10;
    while(l<r){
        ll mid = l+r+1>>1;
        if(check(mid))l = mid;
        else r = mid-1;
    }
    cout<<l<<'\n';
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
