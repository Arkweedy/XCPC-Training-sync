#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,k;
    cin>>n>>m>>k;
    int s, t;
    cin>>s>>t;
    vector<vector<pair<int,int>>>g(n * (k + 1));//mod n
    for(int i = 0;i < m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        //u->v
        for(int j = 0;j <= k;j++){
            g[u + j * n].push_back({v + j * n, w});
            g[v + j * n].push_back({u + j * n, w});
        }
        for(int j = 0;j < k;j++){
            g[u + j * n].push_back({v + (j + 1) * n, 0});
            g[v + j * n].push_back({u + (j + 1) * n, 0});
        }
    }
    //dij(s)

    //ans = min(t, t + n, t + 2n....)
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