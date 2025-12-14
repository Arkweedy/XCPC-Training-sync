#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 3e3 + 10,mod = 998244353;

ll f[N][N],dp[N],res;
ll g[N][N];
ll h[N];

int n,sz[N];
vector<int>e[N];
ll ans;

void dfs1(int u,int fa){
    for(int i=1;i<=n;i++){
        f[u][i] = 0;
    }
    f[u][0] = f[u][1] = 1;
    sz[u] = 1;

    for(auto v:e[u]){
        if(v==fa)continue;
        dfs1(v,u);
        for(int i=1;i<=sz[u]+sz[v];i++)dp[i] = 0;
        for(int i=1;i<=sz[u];i++){
            for(int j=1;j<=sz[v];j++)dp[i+j] = (dp[i+j] + 1ll * f[v][j] * f[u][i]) %mod;
        }
        for(int i=1;i<=sz[u]+sz[v];i++)f[u][i] = (f[u][i] + dp[i])%mod;
        sz[u] += sz[v];
    }
}

void dfs2(int u,int fa){
    int t = 0;
    for(auto v:e[u]){
        if(v==fa)continue;
        t++;
    }
    vector<vector<ll>>pre(t + 1),suf(t + 2);
    pre[0] = {1};
    int cur = 0;
    for(auto v:e[u]){
        if(v==fa)continue;
        cur++;
        int x = pre[cur - 1].size() - 1, y = sz[v];
        for(int i=0;i<=x + y;i++)dp[i] = 0;
        for(int i=0;i<=x;i++){
            for(int j=0;j<=y;j++)dp[i+j] = (dp[i+j] + 1ll * pre[cur-1][i] * f[v][j]) %mod;
        }
        pre[cur].resize(x + y + 1);
        for(int j = 0;j <= x + y;j++){
            pre[cur][j]  = dp[j];
        }
    }
    
    cur = t + 1;
    suf[t + 1] = {1};
    for(int k = e[u].size() - 1;k >=0;k--){
        int v = e[u][k];
        if(v==fa)continue;
        cur--;
        int x = suf[cur + 1].size() - 1, y = sz[v];
        for(int i=0;i<=x + y;i++)dp[i] = 0;
        for(int i=0;i<=x;i++){
            for(int j=0;j<=y;j++)dp[i+j] = (dp[i+j] + 1ll * suf[cur + 1][i] * f[v][j]) %mod;
        }
        suf[cur].resize(x + y + 1);
        for(int j = 0;j <= x + y;j++){
            suf[cur][j]  = dp[j];
        }
    }

    
    h[0] = h[1] = 1;
    for(int i = 1;i <= n - sz[u] + 1;i++){
        h[i + 1] = g[u][i];
    }
    
    //calc g
    cur = 0;
    for(auto v:e[u]){
        if(v==fa)continue;
        cur++;
        for(int i=0;i<=n;i++)dp[i] = 0,g[v][i] = 0;
        //calc g[p] * pre[v - 1] * suf[v + 1]
        int x = pre[cur - 1].size(), y = suf[cur + 1].size();
        
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++)dp[i+j] = (dp[i+j] + 1ll * pre[cur - 1][i] * suf[cur + 1][j]) %mod;
        }

        g[v][0] = 1;
        for(int i = 0;i <= x + y - 2;i++){
            for(int j = 1;j <= n - sz[u] + 1;j++){
                g[v][i + j] = (g[v][i + j] + 1ll * dp[i] * h[j]) % mod;
            }
        }
        
        //calc ans
        for(int i = 1;i <= n;i++){
            ans = (ans + f[v][i] * g[v][i]) % mod;
        }
    }
    
    for(auto v:e[u]){
        if(v==fa)continue;
        dfs2(v,u);
    }
    return;
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
    
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <=sz[i];j++){
            cerr<<f[i][j]<<" ";
        }
        cerr<<endl;
    }
    cerr<<endl;
    

    g[1][0] = 1;
    dfs2(1,0);
    
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <=n - sz[i];j++){
            cerr<<g[i][j]<<" ";
        }
        cerr<<endl;
    }
    cerr<<endl;
    ll res = 0;
    
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            res += f[i][j];
            res %= mod;
        }
    }
    res = (res - ans + mod) % mod;
    cout<<res<<endl;
    return;
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
