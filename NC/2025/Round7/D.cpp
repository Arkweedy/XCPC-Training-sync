#include<bits/stdc++.h>
#define N 31
#define NN 609
#define M 998244353
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using ll=long long ;
const ll INF=0x3f3f3f3f;
using namespace std;
int dp[N][N][N][NN];//u,v,len,sum
struct node{int v,w;};
vector<node> e[N],ee[N];
int n,m,u,v,w;
void work()
{
    for(int i=1;i<=n;i++) dp[i][i][0][0]=0;
    for(int len=0;len<n-1;len++)
    {
        for(int u=1;u<=n;u++)
            for(auto [v,w]:e[u])
            {
                for(int to=1;to<=n;to++) 
                    for(int sum=0;sum<=len*20;sum++)
                         dp[u][to][len+1][sum+w]=min(dp[u][to][len+1][sum+w],w*w+dp[v][to][len][sum]);
            }
    }

}
int vv[N],vvv[N];
void bfs(int st,vector<node> e[N],int vv[])
{
    vv[st]=1;
    queue<int> q;q.push(st);
    while(q.size())
    {
        int p=q.front();q.pop();
        for(auto [v,w]:e[p])
        {
            if(vv[v]) continue;
            q.push(v);vv[v]=1;
        }
    }
}
void solve()
{
    memset(dp,0x3f,sizeof(dp));
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>w;
        e[u].push_back({v,w});
        ee[v].push_back({u,w});
    }
    work();
    long double ans=1e9;
    bfs(1,e,vv);
    bfs(n,ee,vvv);
    for(int len =1;len<n;len++)
    {
        for(int sum=0;sum<=20*len;sum++)
        {
            ans=min(ans,dp[1][n][len][sum]*1.0L/len-1.0L*sum*sum/len/len);
            for(int i=1;i<=n;i++)
                if(vv[i]&&vvv[i])  ans=min(ans,dp[i][i][len][sum]*1.0L/len-1.0L*sum*sum/len/len);
        }
    }
    if(ans>1e3) cout<<-1;
    printf("%.12Lf",ans);
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int tt=1;
   // cin>>tt;
    while(tt--) solve();
    return 0;
}