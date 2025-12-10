#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 3e3 + 10,mod = 998244353;

ll g[N][N],ans[N],f[N];

int n,sz[N];
vector<int>e[N];

void dfs(int u,int f){
    for(int i=1;i<=n;i++){
        g[u][i] = 0;
    }
    g[u][1] = 1;
    ans[1] = (ans[1] + 1)%mod;
    sz[u] = 1;
    for(auto v:e[u]){
        if(v==f)continue;
        dfs(v,u);
        for(int i=1;i<=sz[v];i++){
            for(int j=1;j<=sz[u];j++){
                int k = i + j;
                ans[k] = (ans[k] + g[u][j] * g[v][i])%mod;
            }
        }
        for(int i=1;i<=sz[v];i++)g[u][i] = (g[u][i] + g[v][i]) % mod;
        for(int i=1;i<=sz[v];i++)g[u][i+1] = (g[u][i+1] + g[v][i])%mod;
        
        sz[u] += sz[v];
    }
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)e[i].clear(),ans[i] = 0;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    ll res = 0;
    for(int i=1;i<=n;i++)res = (res + ans[i] * f[i])%mod;
    
    cout<<(res+1)%mod<<'\n';
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    f[1] = 0,f[2] = 1,f[3] = 2;
    for(int i=4;i<N;i++)f[i] = 1ll*(i-1)*(f[i-1]+f[i-2])%mod;
    while(tt--){
        solve();
    }
    return 0;
}
