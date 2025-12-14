#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
int n,m;
vector<ll> vee;

struct node{
    ll k,b,s;
    ll f(ll x)
    {
        return k*x+b;
    }
    
};
void g(node a,node b)
{
    ll p=b.b-a.b,q=a.k-b.k;
   // cout<<p<<q<<endl;
    vee.push_back(p/q);
    vee.push_back(p/q+1);
}
vector<node> ve;
ll gg(int l,int r)
{
   // cout<<l<<' '<<r<<endl;
    if(l>r) return 0;
    node ma=ve[0],mi=ve[1];
    for(auto no:ve)
    {
        if(no.s==-1) continue;
        if(no.f(l)<ma.f(l)) ma=no;
        else if(no.f(l)==ma.f(l)&&no.k<ma.k) ma=no;
    }
    for(auto no:ve)
    {
        if(no.s==1) continue;
        if(no.f(l)>mi.f(l)) mi=no;
        else if(no.f(l)==mi.f(l)&&no.k>mi.k) mi=no;
    }
    ll kk=ma.k-mi.k,bb=ma.b-mi.b;
  //  cout<<kk<<' '<<bb<<endl;
    ll ans=(__int128) kk*(l+r)*(r-l+1)/2+1ll*bb*(r-l+1);
    ans+=r-l+1;
    if(ans<0) return 0;
    return ans;

}
ll cal(int a,int b)
{
    ll ans=0;
    ll l=max(0,a-b),r=min(n,m+a-b);
    if(l>r) return 0;
    ve.clear();
    ve.push_back({0,min(m,a+b),1});
    ve.push_back({0,max(b+a-n,0),-1});
    ve.push_back({-1,m+a,1});
    ve.push_back({-1,a,-1});
    ve.push_back({1,b,1});
    ve.push_back({1,b-n,-1});
   vee.clear();
    for(int i=0;i<6;i++)
        for(int j=i+1;j<6;j++)
            if(ve[i].k!=ve[j].k) g(ve[i],ve[j]);
    vee.push_back(l);
    vee.push_back(r+1);
    sort(vee.begin(),vee.end());
    int m=vee.size();
    for(int i=0;i<m-1;i++)
    {
        int xl=vee[i],xr=vee[i+1];
        if(xl<l) continue;
        if(xl>r) continue;
        ans+=gg(xl,xr-1);
    }
    return ans;
}
void solve()
{
    cin>>n>>m;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++) cout<<cal(i,j)-1<<' ';
        cout<<'\n';
    }
//cout<<cal(0,0);
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
