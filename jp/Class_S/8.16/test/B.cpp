#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using namespace std;
const int N=105;
int n,q,dp[N][N];
vector<pair<int,int> > g[N+1];
void dfs(int p){
    for(auto i:g[p]){
        int x=i.first;
        int y=i.second;
        for(int j=){
            
        }
    }
}
void solve()
{
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
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