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
    for(int i = 0;i < n - 1;i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--,v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<i64>W(n);
    vector<int>fa(n, -1), sz(n, 1), hson(n, -1), dep(n), rfa(n, -1);
    vector<i64>cost(n);
    auto dfs1 = [&](auto&&self, int p) -> void 
    {
        if(isred[p]){
            cost[p] = 0;
            rfa[p] = p;
        }
        for(auto [s, w] : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dep[s] = dep[p] + 1;
                W[s] = W[p] + w;
                cost[s] = cost[p] + w;
                rfa[s] = rfa[p];
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
        i64 x = -1, ma = -1;
        for(auto y : a){
            if(cost[y] > ma){
                ma = cost[y];
                x = y;
            }
        }
        int ra = rfa[x];
        vector<int>na;
        i64 oma = -1;
        for(auto y : a){
            if(rfa[y] == ra){
                na.push_back(y);
            }
            else{
                oma = max(oma, cost[y]);
            }
        }
        a = move(na);
        k = a.size();
        sort(a.begin(),a.end(),[&](int i ,int j)->bool
        {
            return cost[i] > cost[j];
        });
        vector<int>plc(k);
        int lc = a[0];
        for(int i = 0;i < k;i++){
            lc = lca(lc, a[i]);
            plc[i] = lc;
        }
        i64 ans = cost[a[0]];
        int p = 0;
        while(p < k){
            if(p + 1 < k && plc[p] == plc[p + 1])p++;
            else{
                ans = min(ans, max(W[a[0]] - W[plc[p]], (p + 1 < k ? cost[a[p + 1]] : 0ll)));
                p++;
            }
        }
        ans = max(ans, oma);
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