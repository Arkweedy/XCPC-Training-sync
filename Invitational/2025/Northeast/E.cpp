#include<bits/stdc++.h>
#define N 5009
#define M 1000000007
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
int p[N*2],ip[N*2];
int n,k,a[N],dp[N][N],dpp[N][N],s[N],b[N];
vector<int> e[N];
void pre()
{
    p[0]=1;
    for(int i=1;i<2*N;i++) p[i]=1ll*p[i-1]*i%M;
    ip[0]=ip[1]=1;
    for(int i=2;i<2*N;i++) ip[i]=1ll*(M-M/i)*ip[M%i]%M;
    for(int i=2;i<2*N;i++) ip[i]=1ll*ip[i-1]*ip[i]%M;
}
int getc(int a,int b)
{
    if(a<b) return 0;
    return 1ll*p[a]*ip[b]%M*ip[a-b]%M;
}
void dfs(int p,int fa)
{
    s[p]=0;
    if(e[p].size()==1&&fa)
    {
        s[p]=1;
        dpp[p][0]=dpp[p][1]=1;
        dp[p][0]=a[p];
        dp[p][1]=0;
    }
    else 
    {
        dpp[p][0]=1;
        for(int i=0;i<e[p].size();i++)
        {
            int v=e[p][i];
            if(v==fa) continue;
            dfs(v,p);
            for(int i=0;i<=s[p]+s[v];i++ ) b[i]=0;
            for(int i=0;i<=s[p];i++)
                for(int j=0;j<=s[v];j++)
                {
                    b[i+j]=(b[i+j]+1ll*dp[p][i]*dpp[v][j]%M*getc(i+j,i)%M+1ll*dp[v][j]*dpp[p][i]%M*getc(i+j,i))%M;
                }
            for(int i=0;i<=s[p]+s[v];i++ ) dp[p][i]=b[i];
            //if(p==2) for(int i=0;i<s[p]+s[v];i++) cerr<<dp[p][i]<<'\n';
            for(int i=0;i<=s[p]+s[v];i++ ) b[i]=0;
            for(int i=0;i<=s[p];i++)
                for(int j=0;j<=s[v];j++)
                {
                    b[i+j]=(b[i+j]+1ll*dpp[p][i]*dpp[v][j]%M*getc(i+j,i))%M;
                }
            for(int i=0;i<=s[p]+s[v];i++ ) dpp[p][i]=b[i];
            s[p]+=s[v];
        }
        s[p]++;
        dp[p][s[p]]=0;
        dpp[p][s[p]]=0;
        for(int i=s[p];i>=0;i--)
        {
            dp[p][i]=(dp[p][i]+1ll*dpp[p][i]*a[p])%M;
           // if(i) dp[p][i]=(dp[p][i]+dp[p][i-1])%M;
           if(i) dpp[p][i]=(dpp[p][i]+dpp[p][i-1])%M;
        }
    }
//      cerr<<p<<endl;
//      for(int i=0;i<=s[p];i++) cerr<<dp[p][i]<<' ';
//      cerr<<endl;
}
void solve()
{
   cin>>n>>k;
   for(int i=1;i<=n;i++) cin>>a[i];
   for(int i=0;i<=n;i++)
    for(int j=0;j<=n;j++) dp[i][j]=dpp[i][j]=0;
    for(int i=1;i<=n;i++) e[i].clear();
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    cout<<dp[1][k]<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    pre();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}