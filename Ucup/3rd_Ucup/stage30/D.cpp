#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int mod=1e9+7;
ll t,n,q[N],s[N];
ll qmi(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;b>>=1;
    }
    return ans;
}
ll inv(ll a)
{
    return qmi(a,mod-2);
}
int check(int p)
{
    ll sum=t-s[p];
    if(sum<0) return 0;
    return sum/(n-p)>=q[p];
}
void solve()
{
    cin>>t>>n;
    for(int i=1;i<=n;i++) cin>>q[i];
    sort(q+1,q+n+1);
    for(int i=1;i<=n;i++) s[i]=s[i-1]+q[i];
    if(s[n]<=t)
    {
        cout<<1<<' '<<1;
        return ;
    }
    ll pp=1,qq=1;
    for(int i=1;i<=n;i++) qq=qq*q[i]%mod;
    int l=-1,r=n+1;
    while(r-l>1)
    {
        int m=l+r>>1;
        if(check(m)) l=m;
        else r=m;
    }
    for(int i=1;i<=l;i++) pp=pp*q[i]%mod;
    ll a=t-s[l],b=n-l;
    ll k=a/b,kk=a%b;
    for(int i=1;i<=kk;i++) pp=pp*(k+1)%mod;
    for(int i=1;i<=b-kk;i++) pp=pp*k%mod;
    if(!pp)
    {
        cout<<0<<' '<<1;
        return ;
    }
    cout<<inv(qq)<<' '<<inv(pp);

}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
  //  cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
