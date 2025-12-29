#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.25 13:43:35
constexpr int N=1e6+1e5;
int can[N];
int ans[10],a[10],num[10];
ll m,n;
void add(ll p)
{
    //cout<<p<<endl;
    ll pp=p;
    memset(num,0,sizeof(num));
    while(p)
    {
        int s=p%10;p/=10;
        if(s==9) s=6;
        num[s]++;
    }
//    if(pp>1e10) cout<<num[0]<<endl;
    for(int i=0;i<10;i++) ans[i]=max(ans[i],num[i]);
}
int dp[20][1009][2];
vector<int> ve;
int siz,gcdd;
int vis[1009];
int s[20][20];
int INF=1e6;
int dfs(int now,int j,int limit,int zero,int who)
{
    if(now<0)
    {
        //cout<<j<<' '<<vis[j]<<endl;
        if(vis[j]) return 0;
    //    cout<<j<<endl;
        return -INF;
    }
    if(!limit&&dp[now][j][zero]!=-1) return dp[now][j][zero];
    int ans=-INF;
    int ma=9;
    if(limit) ma=ve[now];
    for(int i=0;i<=ma;i++)
    {
        int limi=(limit&&(i==ma));
        if(now<=6&&zero&&!i) continue;
        int zer=zero&&(i==0);


        int con=0;
        if(who==0)
        {
            if(!zero&&i==0) con=1;
        }
        else if(i==who) con=1;
        else if(i==9&&who==6)  con=1;

        //if(who&&con) cout<<12;
        ans=max(ans,con+dfs(now-1,(j+s[now][i])%gcdd,limi,zer,who));
    }
    if(!limit) dp[now][j][zero]=ans;
    return ans;
}
void deal(ll p)
{
    //cout<<p<<endl;
    memset(dp,-1,sizeof(dp));
    ans[p]=max(ans[p],dfs(siz-1,0,1,1,p));
    
}
void solve()
{
    cin>>m>>n;
    ans[0]=1;
    add(m);
    for(int i=1;i<=n;i++) cin>>a[i],gcdd=gcd(gcdd,a[i]);
    can[0]=1;
    for(int i=1;i<N;i++)
    {
        for(int j=1;j<=n;j++)
            if(i>=a[j]) can[i]|=can[i-a[j]];
        if(can[i]&&i<=m&&i<INF) add(i);
    }
    for(int i=0;i<10;i++) s[0][i]=i%gcdd;
    for(int i=1;i<20;i++)
        for(int j=0;j<10;j++) s[i][j]=1ll*10*s[i-1][j]%gcdd;
    if(m>=INF)
    {
        for(int i=1e6;i<1e6+1000;i++)
            if(can[i]) vis[i%gcdd]=1;
        while(m)
        {
            ve.push_back(m%10),m/=10;
        }
        siz=ve.size();
        //cout<<siz<<endl;
        for(int i=0;i<9;i++) deal(i);
    }
    //cout<<m<<endl;
    for(int i=0;i<9;i++)
        if(ans[i]) cout<<i<<' '<<ans[i]<<endl;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}