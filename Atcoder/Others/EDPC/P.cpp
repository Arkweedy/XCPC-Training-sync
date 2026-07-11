#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.10 15:29:44

constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>fa(n, -1);
    vector<int>dp0(n),dp1(n);
    [&](this auto&& dfs, int p)->void
    {
        dp0[p] = dp1[p] = 1;
        for(auto s : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dfs(s);
                dp0[p] = 1ll * dp0[p] * (dp0[s] + dp1[s]) % P;
                dp1[p] = 1ll * dp1[p] * dp0[s] % P;
            }
        }
    }(0);
    
    int ans = (dp0[0] + dp1[0]) % P;
    cout << ans << endl;
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