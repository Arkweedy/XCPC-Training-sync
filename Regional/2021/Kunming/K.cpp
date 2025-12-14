#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,a,b;cin>>n>>a>>b;
    if(a==b)cout<<n<<'\n';
    else if(a==0)cout<<1<<'\n';
    else{
        auto check = [&](ll k)->bool{
            return n <= (b*k+a-1)/a;
        };


        ll l = 1,r = n;
        while(l<r){
            ll mid = l+r>>1;
            if(check(mid))r=mid;
            else l=mid+1;
        }
        cout<<l<<'\n';
    }
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