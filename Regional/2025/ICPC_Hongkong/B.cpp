#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.29 14:23:51

void solve()
{
    int n;
    cin >> n;
    vector<vector<pair<int,i64>>>g(n);
    vector<vector<i64>>dp0(n),dp1(n),dp2(n);
    vector<int>sz(n, 1);
    i64 all = 0;

    for(int i = 0;i < n - 1;i++){
        int u ,v, w;
        cin >> u >> v >> w;
        u-- ,v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        all += w;
    }

    all *= 2;

    auto Max = [&](vector<i64>a, vector<i64>b)->vector<i64>
    {
        a.resize(max(a.size(),b.size()));
        for(int i = 0;i < b.size();i++){
            a[i] = max(a[i], b[i]);
        }
        return a;
    };

    auto add = [&](vector<i64>a, i64 sum, int sz, i64 c)->vector<i64>
    {
        a.resize(a.size() + sz * 2);
        for(int i = a.size() - 1; i - sz * 2 >= 0;i--){
            a[i] = max(a[i], a[i - sz * 2] + sum + 2 * c);
        }
        return a;
    };

    auto mul = [&](vector<i64>&a, vector<i64>&b, i64 cost)->vector<i64>
    {
        int x = a.size(), y = b.size();
        vector<i64>c(x + y + 1);
        for(int i = 0;i < x;i++){
            for(int j = 0;j < y;j++){
                c[i + j + 1] = max(c[i + j + 1], a[i] + b[j] + cost);
            }
        }
        c[x + y] = c[x + y - 1] + cost; 
        return c;
    };

    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        dp0[p].resize(1);
        dp1[p].resize(1);
        dp2[p].resize(1);

        for(auto [s, w] : g[p]){
            if(s != fa){
                self(self, s, p);
                sz[p] += sz[s];
                auto ndp0 = add(dp0[p], dp0[s][sz[s] * 2 - 2], sz[s], w);
                auto ndp1 = Max(add(dp1[p], dp0[s][sz[s] * 2 - 2], sz[s], w), mul(dp0[p], dp1[s], w));
                auto ndp2 = Max(add(dp2[p], dp0[s][sz[s] * 2 - 2], sz[s], w), mul(dp1[p], dp1[s], w));
                dp0[p] = Max(dp0[p], ndp0);
                dp1[p] = Max(dp1[p], ndp1);
                dp2[p] = Max(dp2[p], ndp2);
            }
        }
    };

    dfs(dfs, 0, -1);
    vector<i64>ans(n * 2 - 1);
    dp0[0].resize(n * 2 - 1);
    dp1[0].resize(n * 2 - 1);
    dp2[0].resize(n * 2 - 1);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < dp0[i].size();j++){
            dp0[0][j] = max(dp0[0][j], dp0[i][j]);
        }
        for(int j = 0;j < dp1[i].size();j++){
            dp1[0][j] = max(dp1[0][j], dp1[i][j]);
        }
        for(int j = 0;j < dp2[i].size();j++){
            dp2[0][j] = max(dp2[0][j], dp2[i][j]);
        }
    }
    for(int i = 0;i <= n * 2 - 2;i++){
        //cerr << dp0[0][i] << " " << dp1[0][i] << endl;
        ans[i] = all - max(max(dp0[0][i], dp1[0][i]), dp2[0][i]);
    }
    for(int i = 0;i <= n * 2 - 2;i++){
        cout << ans[i] << " ";
    }
    cout << endl;
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