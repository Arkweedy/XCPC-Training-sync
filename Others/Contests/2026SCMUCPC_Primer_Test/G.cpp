#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.05.09 19:41

//O(n)

void solve()
{
    int n, k, s, t;
    cin >> n >> k >> s >> t;
    s--,t--;
    vector<int>sk(n);
    for(int i = 0;i < k;i++){
        int e;
        cin >> e;
        e--;
        sk[e] = 1;
    }

    vector<vector<array<int,3>>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--,v--;
        g[u].push_back({v, x, y});
        g[v].push_back({u, x, y});
    }

    constexpr i64 inf = 1e18;
    vector<int>fa(n, -1);
    vector<i64>a(n, inf), b(n, inf);//0 -> 1, 1 -> 0 cost
    vector<int>fx(n),fy(n);
    int c = 0;
    auto dfs = [&](auto&&self, int p)->void
    {
        c++;
        for(auto [s, x, y] : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                fx[s] = x;
                fy[s] = y;
                self(self, s);
                a[p] = min(a[p], a[s] + x + y);
                b[p] = min(b[p], b[s] + x + y);
            }
        }
        if(sk[p]){
            a[p] = b[p] = 0;
        }
    };
    dfs(dfs, t);
    //assert(c == n);
    i64 ca = 0, cb = inf;
    int p = s;
    while(p != t){
        i64 nca = min(ca + fx[p], cb + b[p] + fx[p]);
        i64 ncb = min(cb + fy[p], ca + a[p] + fy[p]);
        ca = nca;
        cb = ncb;
        p = fa[p];
    }
    i64 ans = min(ca, cb);
    cout << ans << endl;
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