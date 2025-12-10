#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll k,a,b,x,y;
    cin>>k>>a>>b>>x>>y;
    if(x > y){
        swap(x,y);
        swap(a,b);
    }
    int ans = 0;
    if(k >= a){
        int c1 = (k - a) / x + 1;
        ans += c1;
        k -= 1ll * c1 * x;
    }
    if(k >= b){
        int c = (k - b) / y + 1;
        ans += c;
        k -= c * y;
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