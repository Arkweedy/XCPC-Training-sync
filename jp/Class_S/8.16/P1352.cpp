#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 6e3 + 10;
vector<vector<int>>g(N);
vector<array<int,2>>dp(N);
vector<int>w(N);

void dfs(int p)
{
    dp[p][0] = 0;
    dp[p][1] = w[p];
    for(auto s : g[p]){
        //dep[s] = dep[p] + 1;
        dfs(s);
        //sz[p] += sz[s];
        dp[p][0] += max(dp[s][0],dp[s][1]);
        dp[p][1] += dp[s][0];
    }
    return;
}



void solve()
{
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++){
        cin>>w[i];
    }
    vector<int>is(n + 1, 1);
    for(int i = 1;i <= n - 1;i++){
        int u,v;
        cin>>u>>v;
        g[v].push_back(u);
        is[u] = 0;
    }
    int x;
    for(int i = 1;i <= n;i++){
        if(is[i]){
            x = i;
            dfs(i);
        }
    }
    cout<<max(dp[x][0],dp[x][1])<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}