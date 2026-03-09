#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.09 00:15:44

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>isl(n);
    vector<int>nlf(n);
    for(int i = 0;i < n;i++){
        if(g[i].size() == 1){
            isl[i] = 1;
            nei[g[i][0]] = 1;
        }
    }

    
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