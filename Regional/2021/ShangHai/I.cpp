#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e2 + 10;
constexpr int T=2600;
ll dp[2][N][T*3];
int n,kk,v[N],t[N];
void solve()
{
    cin>>n>>kk;
    for(int i=0;i<n;i++) cin>>v[i]>>t[i];
    memset(dp,-0x3f,sizeof(dp));
    dp[0][0][T]=0;
    for(int i=0;i<n;i++)
    {
        int no=i&1;int ne=no^1;
        memset(dp[ne],-0x3f,sizeof(dp[ne]));
        for(int j=0;j<=i&&j<=kk;j++)
            for(int k=0;k<=2*T;k++)
            {
                ll a=dp[no][j][k];
                dp[ne][j][k]=max(dp[ne][j][k],a);
                if(k+t[i]<=2*T) dp[ne][j][k+t[i]]=max(dp[ne][j][k+t[i]],a+v[i]);
                if(k-t[i]>=0) dp[ne][j][k-t[i]]=max(dp[ne][j][k-t[i]],a+v[i]);
                if(k+2*t[i]<=2*T) dp[ne][j+1][k+2*t[i]]=max(dp[ne][j+1][k+2*t[i]],a+v[i]);
                if(k-2*t[i]>=0) dp[ne][j+1][k-2*t[i]]=max(dp[ne][j+1][k-2*t[i]],a+v[i]);
            }
        //if(i==0) cout<<dp[ne][1][2+T]<<endl;
    }
    ll ans=0;
    for(int i=0;i<=kk;i++) ans=max(ans,dp[n&1][i][T]);
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