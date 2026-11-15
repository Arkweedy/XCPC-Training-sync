#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
 
using namespace std;
ll a,b,ha,hb;
void solve()
{
    cin>>a>>b>>ha>>hb;
    ll ta=(ha+b-1)/ b;
    ll tb=(hb+a-1)/a;
    if(ta-tb>=4) cout<<"YES\n";
    else cout<<"NO\n";
} 

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}