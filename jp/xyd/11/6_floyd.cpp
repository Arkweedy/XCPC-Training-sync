#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    constexpr int inf = 11451419;
    vector<vector<int>>d(n,vector<int>(n,inf));
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        d[u][v] = d[v][u] = 1;
    }
    for(int i = 0;i < n;i++){
        d[i][i] = 0;
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