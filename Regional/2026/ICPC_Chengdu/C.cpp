#include<bits/stdc++.h>
#define N 109
using ll = long long;
using i64 = long long;

using namespace std;
constexpr int mod=998244353;
int dp[N][N][N*N];
int g[N][N],v[N];
int n,m;
void solve()
{
    cin>>n>>m;
    v[1]=0;
    int err=0;
    for(int i=2;i<=n;i++) v[i]=-1;
    int ma=1;
    for(int i=1;i<=m;i++){
        int p,x;
        cin>>p>>x;
        ma=max(ma,p);
        if(v[p]==-1) v[p]=x;
        if(v[p]!=x) {err=1;}
        v[p]=x;
    }
    if(err){cout<<0<<'\n';return ;}
    vector<pair<int,int> >ve;
    for(int i=0;i<=n;i++)
        for(int j=0;j<n;j++) g[i][j]=0;
    
    for(int i=1;i<=n;i++) {
        if(v[i]>=0) ve.push_back({i,v[i]});
    }
    g[1][0]=1;
    int s=ve.size();
    for(int i=1;i<s;i++){
        auto [ni,nv]=ve[i];
        auto [pi,pv]=ve[i-1];
        int len=ni-pi;
        int s=nv-pv;
        vector<int> v;
        for(int i=0;i<pi;i++){
            if(i*len>s) continue;
            if(i*len+len*(len+1)/2<s) continue;
            v.push_back(i);
        }
        for(int j=0;j<ni;j++)
            for(auto p:v){
                if(p>j) continue;
                int num =j-p;
                int ss=s-p*len;
                g[ni][j]=(g[ni][j]+1ll*g[pi][p]*dp[len][num][ss])%mod;
            }
    }

    
    int ans=0;
    for(int i=0;i<n;i++) ans=(ans+g[ma][i])%mod;
    for(int i=0;i<n-ma;i++) ans=1ll*ans*2%mod;
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    dp[0][0][0]=1;
    for(int i=1;i<N;i++)
        for(int j=0;j<=i;j++)
            for(int k=0;k<=i*(i+1)/2;k++){
                if(k<j) continue;
                dp[i][j][k]=dp[i-1][j][k-j];
                if(j) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-1][k-j])%mod;
            }
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}