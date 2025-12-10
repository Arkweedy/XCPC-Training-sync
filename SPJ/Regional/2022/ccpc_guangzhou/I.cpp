#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 2e3 + 10,mod = 1e9+7;

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}


vector<ll>dp[N][2];
int n,sz[N],pa[N];
ll a[N],p[N];
vector<int>e[N];

void dfs(int u,int fa){
    sz[u] = 1,pa[u] = fa;
    dp[u][0] = {0,p[u]};
    dp[u][1] = {0,a[u]};
    for(auto v:e[u]){
        if(v==fa)continue;
        dfs(v,u);

        vector<vector<ll>>ndp(2,vector<ll>(sz[u]+sz[v]+1));

        
        for(int x=0;x<2;x++){
            for(int y=0;y<2;y++){
                if(x && y)continue;
                for(int i=1;i<=sz[u];i++){
                    for(int j=1;j<=sz[v];j++){
                        int z = x | y;
                        ndp[z][i+j] = (ndp[z][i+j] + dp[u][x][i] * dp[v][y][j]) % mod;
                    }
                }
            }
        }
            
        for(int i=1;i<=sz[u];i++){
            for(int x=0;x<2;x++){
                ndp[x][i] = (ndp[x][i] + dp[u][x][i] * (1-p[v] + mod))%mod;
            }
        }

        sz[u] += sz[v];
        dp[u][0] = ndp[0],dp[u][1] = ndp[1];
    }
}

void solve()
{
    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    ll sum = 0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum += a[i];
        ll b,c;cin>>b>>c;
        p[i] = b * qmi(c,mod-2)%mod;
    }
    sum = qmi(sum,mod-2);
    for(int i=1;i<=n;i++)a[i] = a[i] * sum % mod;
    dfs(1,0);

    for(int i=1;i<=n;i++){
        ll res = 0;
        for(int j=1;j<=n;j++){
            if(sz[j] >= i)res = (res + dp[j][1][i] * (1-p[pa[j]]+mod))%mod;
        }
        cout<<(res+mod)%mod<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}