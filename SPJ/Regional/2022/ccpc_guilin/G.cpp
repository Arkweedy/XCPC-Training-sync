#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 2e5 + 10;
vector<int>e[N];
int n;
ll a[N],mx[N][4],dp[N],g[N],f[N],res,ndp[N];

void dfs1(int u,int fa){
    for(auto v:e[u]){
        if(v==fa)continue;
        dfs1(v,u);
        dp[u] = max(dp[u],dp[v]);
        ll cur = f[v] + a[v];
        for(int i=0;i<4;i++){
            if(cur > mx[u][i]){
                swap(cur,mx[u][i]);
            }
        }
    }
    dp[u] = max(dp[u],mx[u][0] + mx[u][1] + a[u]);
    f[u] = mx[u][0];
}

void dfs2(int u,int fa){
    ll cur = g[u];
    for(int i=0;i<4;i++){
        if(cur > mx[u][i]){
            swap(cur,mx[u][i]);
        }
    }
    res = max(res,mx[u][0] + mx[u][1] + mx[u][2] + mx[u][3]);
    ll mdp[2] = {0,0},len[3] = {g[u],0,0};
    for(auto v:e[u]){
        if(v==fa)continue;
        ll cur = f[v] + a[v];
        for(int i=0;i<3;i++){
            if(cur > len[i]){
                swap(cur,len[i]);
            }
        }
        cur = dp[v];
        for(int i=0;i<2;i++){
            if(cur > mdp[i]){
                swap(cur,mdp[i]);
            }
        }
    }
    for(auto v:e[u]){
        if(v==fa)continue;
        bool flg = 0;
        vector<ll>c;
        for(int i=0;i<3;i++){
            if(!flg && len[i] == f[v] + a[v]){
                flg = 1;
            }else{
                c.push_back(len[i]);
            }
        }
        sort(c.begin(),c.end(),greater<ll>());
        ll ans = mdp[0] == dp[v] ? mdp[1] : mdp[0];
        ans = max({ans,c[0] + c[1] + a[u],ndp[u]});
        res = max(res,ans + dp[v]); 
        ndp[v] = ans;
        g[v] = a[u] + c[0];
        dfs2(v,u);
    }
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);

    cout<<res<<'\n';
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