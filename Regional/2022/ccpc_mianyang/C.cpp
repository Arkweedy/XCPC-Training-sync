#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

vector<int>e[N];
int dep[N];

int dfs(int u,int f){
    dep[u] = dep[f] + 1;
    int mx = dep[u];
    for(auto v:e[u]){
        if(v==f)continue;
        int t = dfs(v,u);
        mx = max(mx,t);
    }
    return mx;
}

void solve()
{
    int n;cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    ll res = 0;
    for(auto u:e[1]){
        res += dfs(u,1);
    }
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
