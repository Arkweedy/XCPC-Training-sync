#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
constexpr int mod=1e9+7;
ll n,m,k;
ll dp[41][20][100];
int p[N],ip[N];
void pre()
{
    p[0]=1;
    for(int i=1;i<N;i++) p[i]=1ll*i*p[i-1]%mod;
    ip[0]=ip[1]=1;
    for(int i=2;i<N;i++) ip[i]=1ll*(mod-mod/i)*ip[mod%i]%mod;
    for(int i=2;i<N;i++) ip[i]=1ll*ip[i]*ip[i-1]%mod;
}
int getc(int a,int b)
{
    if(a<b||a<0||b<0) return 0;
    return 1ll*p[a]*ip[b]%mod*ip[a-b]%mod;
}
void solve()
{
    pre();
    cin>>n>>m>>k;
    if((n>>40)<100) dp[40][k][n>>40]=1;
    for(int i=40;i;i--)
        for(int j=0;j<=k;j++)
            for(int s=0;s<100;s++)
            {
                int op=(m>>(i-1))&1;
                int opp=(n>>(i-1))&1;
                if(!op)
                {
                    for(int b=0;b<=k-j;b++) //1
                    {
                        int ss=s*2-b*(k-b)+opp;
                        if(ss>=0&&ss<100) dp[i-1][j][ss]=(dp[i-1][j][ss]+dp[i][j][s]*getc(k-j,b))%mod;
                    }
                }
                else 
                {
                    for(int a=0;a<=j;a++)
                        for(int b=0;b<=k-j;b++)
                        {
                            int num1=a+b;
                            int ss=s*2-num1*(k-num1)+opp;
                            if(ss>=0&&ss<100) dp[i-1][a][ss]=(dp[i-1][a][ss]+dp[i][j][s]*getc(j,a)%mod*getc(k-j,b))%mod;
                        }
                }
            }
    ll ans=0;
    for(int i=0;i<=k;i++) ans=(ans+dp[0][i][0])%mod;
    ans=(ans+mod)%mod;
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}