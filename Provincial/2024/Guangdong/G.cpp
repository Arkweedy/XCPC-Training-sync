#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 15:16:21

void solve()
{
    ll l ,r;
    cin>>l>>r;
    ll ans=  0;
    for(ll L = 1, R;L <= r;L = R + 1){
        R = r / (r / L);
        ll a = (l + R - 1) / R;
        ll b = r / R;
        if(a + 1 <= b)ans = max(ans, R);
    }
    cout<<ans<<endl;
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