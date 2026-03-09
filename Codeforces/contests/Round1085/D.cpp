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
    int rt, k;
    cin >> k >> rt;
    rt--;
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
    for(int i = 0;i < n;i++){
        if(g[i].size() == 1){
            isl[i] = 1;
        }
    }

    constexpr int inf = 1e9;
    vector<array<int,2>>dp(n, {inf, inf});
    
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        if(isl[p]){
            dp[p] = {0, inf};
            return;
        }
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                // can O(k)
                for(int i = 0;i < 2;i++){
                    int x = dp[s][i] + 1;
                    for(int j = 0;j < 2;j++){
                        if(x < dp[p][j])swap(x, dp[p][j]);
                    }
                }
            }
        }
        if(dp[p][0] + dp[p][1] < k + 2){
            dp[p] = {0, inf};
            isl[p] = 1;
        }
        return;
    };
    dfs(dfs, rt, -1);

    if(isl[rt]){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
    return;
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