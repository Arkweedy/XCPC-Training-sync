#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.30 10:32:49

void solve()
{
    ll a,b,c;
    cin>> a>>b>>c;
    ll ans = b * 2 - (a + c);
    if(ans < 0){
        if(ans % 2 == -1)ans-=3;
        ans = - ans / 2;
    }
    cout<<ans<<endl;
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