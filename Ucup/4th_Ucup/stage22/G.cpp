#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
constexpr int N =3009;
using namespace std;
constexpr int mod=998244353;
vector<int> e[N];
int dp[N][N],s[N];
int f[N],n,k;
void dfs(int p,int fa){
    s[p]=1;
    for(auto v:e[p]){
        if(v==fa) continue;
        dfs(v,p);
        s[p]+=s[v];
    }
    for(int i=0;i<=n;i++){
        dp[p][i]=1;
        for(auto v:e[p]){
            if(v==fa) continue;
            dp[p][i]=1ll*dp[p][i]*dp[v][i]%mod;
        }
    }
    if(p!=1){
        for(int i=1;i<=n;i++) dp[p][i]=(dp[p][i]+dp[p][i-1])%mod;
    }
}
ll qp(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;b>>=1;
    }
    return ans;
}
int inv(int p){
    if(p<0) p+=mod;
    return qp(p,mod-2);
}
int get(int k){
    for(int i=0;i<=n;i++) f[i]=dp[1][i];
    if(k<=n) return f[k];
    int ans=0;
    for(int i=0;i<=n;i++){
        int con=dp[1][i];
        for(int j=0;j<=n;j++){
            if(i==j ) continue;
            con=1ll*con*(k-j)%mod;
            con=1ll*con*inv(i-j)%mod;
        }
        ans=(ans+con)%mod;
    }
    return ans;
}
void solve()
{ 
   
    cin>>n>>k;
    for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);e[v].push_back(u);
    }
  //  cout<<n<<endl;
    dfs(1,0);
  //  for(int i=0;i<=n;i++) cout<<dp[1][i]<<endl;
    cout<<get(k);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}