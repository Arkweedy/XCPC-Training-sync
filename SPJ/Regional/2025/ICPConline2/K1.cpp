#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 3e3 + 10,mod = 998244353;

ll f[N][N],dp[N];

int n,sz[N];
vector<int>e[N];
ll ans;

void dfs1(int u,int fa){
    for(int i=1;i<=n;i++){
        f[u][i] = 0;
    }
    f[u][0] = f[u][1] = 1;
    sz[u] = 1;
    //with pre
    for(auto v:e[u]){
        if(v==fa)continue;
        dfs1(v,u);
        for(int i=1;i<=sz[u]+sz[v];i++)dp[i] = 0;
        for(int i=1;i<=sz[u];i++){
            for(int j=1;j<=sz[v];j++){
                dp[i+j] = (dp[i+j] + 1ll * f[v][j] * f[u][i]) %mod;
            }
        }
        for(int i=1;i<=sz[u]+sz[v];i++)f[u][i] = (f[u][i] + dp[i])%mod;
        sz[u] += sz[v];
    }
}

void calc(int u,int fa,int B){
    for(int i=1;i<=B;i++){
        f[u][i] = 0;
    }
    f[u][1] = 1;
    int cur = 1;
    for(auto v:e[u]){
        if(v==fa)continue;
        for(int i=1;i<= min(B,cur + sz[v]);i++)dp[i] = 0;
        for(int i=1;i<=cur;i++){
            if(i>B)break;
            for(int j=1;j<=sz[v];j++){
                if(i+j>B)break;
                dp[i+j] = (dp[i+j] + 1ll * f[v][j] * f[u][i]) %mod;
            }
        }
        for(int i=1;i<= min(B,cur + sz[v]);i++)f[u][i] = (f[u][i] + dp[i])%mod;
    }
}

void dfs2(int u,int fa){
    for(auto v:e[u]){
        if(v==fa)continue;
        int B = min(sz[v],n-sz[v]);
        calc(u,v,B);
        for(int i=1;i<=B;i++)ans = (ans + f[u][i] * f[v][i])%mod;
        dfs2(v,u);
    }
}

void solve()
{
    ans = 0;
    cin>>n;
    for(int i=1;i<=n;i++)e[i].clear();
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);

    ll res = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= sz[i];j++){
            res += f[i][j];
        }
    }


    dfs2(1,0);

    
    res = (res - ans + mod)%mod;
    cout<<res<< '\n';
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
