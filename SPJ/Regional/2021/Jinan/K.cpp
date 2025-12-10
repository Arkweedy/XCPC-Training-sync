#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

using ld = long double;

const int N = 110;

vector<int>e[N];
ld dp[N];
int n,sz[N];

void dfs(int u,int f){
    dp[u] = 0;
    sz[u] = 0;
    for(auto v:e[u]){
        if(v==f)continue;
        dfs(v,u);
        dp[u] += sz[v] * (dp[v]+1) + 2ll * sz[v] * sz[u];
        sz[u] += sz[v];
    }
    sz[u] ++;
    dp[u]/=sz[u];
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        e[i].clear();
    }
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    cout<<fixed<<setprecision(10);
    cout<<dp[1] * n/(n-1)<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}