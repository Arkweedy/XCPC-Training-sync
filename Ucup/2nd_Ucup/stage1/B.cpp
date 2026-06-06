#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.05.27 15:15

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<pair<int,int>>>g(n);
    
    vector<int>isred(n);
    for(int i = 0;i < m;i++){
        int x;
        cin >> x;
        x--;
        isred[x] = 1;
    }
    for(int i = 0;i < n -1;i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--,v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<i64>W(n);
    vector<int>fa(n, -1), sz(n, 1), hson(n, -1), dfn(n), dep(n);
    vector<i64>cost(n);
    int tot = 0;
    auto dfs1 = [&](auto&&self, int p) -> void 
    {
        dfn[p] = tot++;
        if(isred[p])cost[p] = 0;
        for(auto [s, w] : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dep[s] = dep[p] + 1;
                W[s] = W[p] + w;
                cost[s] = cost[p] + w;
                self(self, s);
                sz[p] += sz[s];
                if(hson[p] == -1 || sz[s] >= sz[hson[p]]){
                    hson[p] = s;
                }
            }
        }
        return;
    };
    dfs1(dfs1, 0);
    vector<int>top(n);
    auto dfs2 = [&](auto&&self, int p)->void
    {
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            self(self, hson[p]);
        }
        for(auto [s, w] : g[p]){
            if(s != fa[p] && s != hson[p]){
                top[s] = s;
                self(self, s);
            }
        }
    };
    dfs2(dfs2, 0);
    auto lca = [&](int u, int v)->int
    {
        while(top[u] != top[v]){
            if(dep[top[u]] < dep[top[v]]){
                v = fa[top[v]];
            }
            else{
                u = fa[top[u]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };

    vector<vector<int>>vg(n);
    vector<i64>dp0(n),dp1(n), dp2(n);
    //dp0 : no modify
    //dp1 : 1 modify
    //dp2 : no modify, greatest point

    auto dfs3 = [&](auto&&self, int p)->void
    {
        dp0[p] = cost[p];
        dp1[p] = 0;
        dp2[p] = W[p];
        for(auto s : vg[p]){
            self(self, s);
            if(isred[p]){
                dp1[p] = min(max(dp1[p], dp0[s]), max(dp0[p], dp1[s]));
                dp0[p] = max(dp0[p], dp0[s]);
            }
            else{
                //dp1[p] = min(max(dp1[p], dp2[s] - W[p]), max(dp1[s], dp0[p]));
                //dp0[p] = max(dp0[p], dp0[s]);
            }
        }
        return;
    };

    while(q--){
        int k;
        cin >> k;
        vector<int>a(k);
        for(int i = 0;i < k;i++){
            cin >> a[i];
            a[i]--;
        }
        if(k == 1){
            cout << 0 << endl;
            continue;
        }
        sort(a.begin(),a.end(),[&](int i ,int j)->bool
        {
            return dfn[i] < dfn[j];
        });
        for(int i = 0;i < k - 1;i++){
            a.push_back(lca(a[i], a[i + 1]));
        }
        sort(a.begin(),a.end(),[&](int i ,int j)->bool
        {
            return dfn[i] < dfn[j];
        });
        a.erase(unique(a.begin(),a.end()),a.end());
        int t = a.size();
        for(auto x : a){
            vg[x].clear();
        }
        for(int i = 0;i < t - 1;i++){
            int lc = lca(a[i], a[i + 1]);
            vg[lc].push_back(a[i + 1]);
        }
        dfs3(dfs3, a[0]);
        i64 ans = min(dp0[a[0]], dp1[a[0]]);
        cout << ans << endl;
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