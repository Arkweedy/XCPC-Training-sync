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
void solve()
{
    ll x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    ll A = y1 -y2,B = x2-x1;
    ll C = A * x1 + B * y1;
    ll opA = A/abs(A),opB = B / abs(B);
    A = abs(A),B = abs(B);
    auto [x,y] = exgcd(A,B,gcd(A,B));
    assert(x * A + y * B == gcd(A,B));
    cout<<x1+x * opA<<' '<<y1+y * opB<<'\n';
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