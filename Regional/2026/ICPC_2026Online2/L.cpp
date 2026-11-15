#include<bits/stdc++.h>
#define N 1000009
using i64 = long long;
using ll = long long;
using namespace std;
ll n,a[N],f[N];
ll ans;
void deal(){
    for(int i=1;i<n;i++) f[i]=a[i]+a[i+1];
    ll sum=0;
    for(int i=1;i<n;i++){
        sum+=f[i];
        ans=min(ans,sum+(n-1-i)*f[i]);
    }
}
void solve()
{
    ans=1e18;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(n==1){
        cout<<a[1]<<'\n';return ;
    }
    deal();
    reverse(a+2,a+n+1);
    deal();
    cout<<ans+a[1]<<'\n';
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



