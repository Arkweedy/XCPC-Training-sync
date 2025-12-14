#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e6 + 10;

int n,u,v,a[N];
struct node
{
    ll ans[4];
    int l,r;
}dp[N];
vector<int> e[N];
struct node1{int p,t,a;};
bool cmpl(node1 a,node1 b)
{
    if(a.a!=b.a)  return a.a<b.a;
    return a.t>b.t;
}
bool cmpr(node1 a,node1 b)
{
    if(a.a!=b.a)  return a.a>b.a;
    return a.t<b.t;
}
void dfs(int p,int fa)
{
    for(auto v:e[p])
    {
        if(v==fa) continue;
        dfs(v,p);
    }
    int lp=0,rp=0;
    vector<node1> ve;
     for(auto v:e[p])
    {
        if(v==fa) continue;
        if(a[v]>a[p]) ve.push_back({v,dp[v].r,a[v]});
    }
    sort(ve.begin(),ve.end(),cmpr);
    if(ve.size()) rp=ve[0].p;
    
    ve.clear();
     for(auto v:e[p])
    {
        if(v==fa) continue;
        if(a[v]<a[p]) ve.push_back({v,dp[v].l,a[v]});
    }
    sort(ve.begin(),ve.end(),cmpl);
    if(ve.size()) lp=ve[0].p;
    ll sum=0;
     for(auto v:e[p])
    {
        if(v==fa) continue;
       sum+=dp[v].ans[3];
    }
    for(int j=0;j<3;j++) dp[p].ans[j]=sum;
    dp[p].l=dp[p].r=a[p];
    if(lp)
    {
        dp[p].l=dp[lp].l;
        dp[p].ans[0]=max(dp[p].ans[0],sum-dp[lp].ans[3]+dp[lp].ans[0]+abs(a[p]-a[lp]));
    }
    if(rp)
    {
        dp[p].r=dp[rp].r;
        dp[p].ans[1]=max(dp[p].ans[1],sum-dp[rp].ans[3]+dp[rp].ans[1]+abs(a[p]-a[rp]));
    }
    if(lp&&rp)
    {
        dp[p].ans[2]=max(dp[p].ans[2],sum-dp[lp].ans[3]+dp[lp].ans[0]+abs(a[p]-a[lp])-dp[rp].ans[3]+dp[rp].ans[1]+abs(a[p]-a[rp]));
    }
    for(int j=0;j<3;j++) dp[p].ans[3]=max(dp[p].ans[3],dp[p].ans[j]);
 }
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
   dfs(1,0);
   for(int i=1;i<=n;i++) 
   {
       for(int j=0;j<3;j++) cout<<dp[i].ans[j]<<' ';
       cout<<endl;
   }
   cout<<dp[1].ans[3];
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
   // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
