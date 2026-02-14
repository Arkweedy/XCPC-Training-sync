#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.13 17:48
constexpr int P = 998244353;

int power(int a,int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin >> u >> v;
        u--,-v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector<int>sz(n, 1);
    vector<i64>dp0(n), dp1(n), dp2(n);
    i64 ans = 0;
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        dp0[p] = dp1[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                //00 01 10 (11 -> calced)
                i64 c0 = 0, c1 = 0, c2 = 0;
                sz[p] += sz[s];
                // and
                c0 += 1ll * dp0[p] * dp0[s] + 1ll * dp0[p] * dp1[s] + 1ll * dp1[p] * dp0[s];
                c1 += 1ll * dp1[p] * dp1[s];
                c2 += 1ll * (dp0[p] + dp1[p]) * dp2[s] % P + 1ll * (dp0[s] + dp1[s] + dp2[s]) * dp2[p] % P;
                // or
                c0 += 1ll * dp0[p] * dp0[s];
                c1 += 1ll * dp1[p] * dp0[s];
                c2 += 1ll * (dp1[p] + dp0[p] + dp2[p]) * (dp1[s] + dp2[s]) % P + dp0[s] * dp2[p];


                dp0[p] = c0 % P;
                dp1[p] = c1 % P;
                dp2[p] = c2 % P;
            }
        }
        //ans = (ans + 1ll * dp1[p] * power(2, max(2 * n - sz[p] * 2 - 1, 0))) % P;
        return;
    };
    dfs(dfs, 0, -1);
    ans = (dp1[0] + dp2[0]) % P;
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