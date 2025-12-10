#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 1000000007;

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

//48pts
void solve()
{
    int n;
    cin>>n;
    ll ans = 0;
    for(ll l = 1,r;l <= n;l = r + 1){
        r = n / (n / l);
        ans += (n / l) * (r - l + 1);
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