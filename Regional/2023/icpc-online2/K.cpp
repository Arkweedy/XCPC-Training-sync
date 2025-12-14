#include<bits/stdc++.h>
#define N 100009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using namespace std;
using ll =long long ;
const ll INF =1e18;
const int mod=998244353;
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
ll gcdd(ll a,ll b ,ll g)//gcd(a*b,g);
{
    ll d=gcd(a,g);
    g/=d;
    d*=gcd(b,g);
    return d;
}
pair<ll,ll> exgcd(ll a,ll b, ll c)
{
    ll d=gcd(a,b);
    if(c%d) return {-1,-1};
    if(!b) return {c/a,0};
    ll x=1,x1=0,p=a,q=b,k;
    ll mod=abs(b/d);
    while(b)
    {
        k=a/b;
        x-=k*x1;
        a-=k*b;
        swap(x,x1);
        swap(a,b);
    }
     x=(__int128) x*(c/d)%mod;
     if(x<0) x+=mod;
     return {x,mod};
}
pair<ll,ll>  cal(ll a,ll r ,ll p)
{
    auto [x,mod]=exgcd(a,p,r);
    if(x==-1&&mod==-1) return {-1,-1};
    return {x,mod};
}
ll a,b,n;
void solve()
{   
    cin>>a>>b>>n;
    ll aa=a%n,bb=b%n;
    ll ans=aa*aa+bb*bb;
    for(int i=0;i<n&&i<=150;i++)
    {
        auto [r,p]=cal(a,i,n);
        if(r==-1&&p==-1) continue;
        ll pp=gcdd(b,p,n);
        ll y=(__int128)b*r%pp;
        if(i==0) 
        {
            y=pp%n;
            if(y&&y<=200) ans=min(ans,y*y);
        }
        else if(y<=200) ans=min(ans,y*y+i*i);
    }
    cout<<ans<<'\n';
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    cin>>tt;
    while(tt--) solve();
    return 0;
}