#include<bits/stdc++.h>

using ll = long long;
using namespace std;

#define int long long 
constexpr int N = 1e5 + 10;
ll n,a[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    //cout<<1;return ;
    int g=0;
    for(int i=1;i<=n;i++) g=gcd(g,abs(a[i]-a[1]));
    if(!g)
    {
        cout<<"infinite\n";
        return ;
    }
    int t=a[1]%g;
    //cout<<t<<endl;
    cout<<g<<' '<<g/gcd(t,g)<<'\n';
}

signed main()
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