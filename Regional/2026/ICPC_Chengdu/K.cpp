#include<bits/stdc++.h>
#define N 200009
using ll = long long;
using i64 = long long;
 
using namespace std;
ll a[N],l[N],n;
int check(ll len){
    ll ma=a[1]+len,mi=a[1]-len;
    for(int i=2;i<=n;i++){
        ll maa=-8e18,mii=8e18;
        ll pl1=max(a[i]-len,mi+l[i-1]),pr1=a[i]+len;
        if(pl1<=pr1) maa=max(maa,pr1),mii=min(mii,pl1);
        ll pl2=a[i]-len,pr2=min(a[i]+len,ma-l[i-1]);
        if(pl2<=pr2)  maa=max(maa,pr2),mii=min(mii,pl2);
        if(mii>maa)return 0;
        mi=mii;ma=maa;
    }
    return 1;
}
void solve()
{   
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++)cin>>l[i];
    ll pl=-1,pr=1e18;
    while(pr-pl>1){
        ll m=pl+pr>>1;
        if(check(m)) pr=m;
        else pl=m;
    }
    cout<<pr<<'\n';

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