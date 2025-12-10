#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
pair<ll,ll> exgcd(ll a,ll b,ll c){
    assert(a||b);
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

    x=x*(c/d)%mod;
    if(x<0) x+=mod;
    return {x,(c-p*x)/q};
}
ll x,y,xx,yy;
void solve()
{
    cin>>x>>y>>xx>>yy;
    ll a=yy-y,b=x-xx;
    ll d=gcd(a,b);
    a/=d,b/=d;
    ll c=a*x+b*y;
    c--;
    auto [ansx,ansy]= exgcd(a,b,c);
    cout<<ansx<<' '<<ansy<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}