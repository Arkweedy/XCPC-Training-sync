#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
ll p,q;
ll f(ll p)
{
    if(p<0) return -1;
    ll m=sqrt(p);
    for(ll i=max(m-5,0ll);i<=m+5;i++)
        if(i*i==p) return i;
    return -1;
}
ll gcd(ll a,ll b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
void solve()
{
    cin>>p>>q;
    ll g=f(p*p-4*q*q);
    if(g<0) 
    {
        cout<<0<<' '<<0<<'\n';
        return ;
    }
    ll a=p-g,b=2*q;
    ll d=gcd(a,b);
    a/=d;b/=d;
    cout<<a<<' '<<b<<'\n';
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