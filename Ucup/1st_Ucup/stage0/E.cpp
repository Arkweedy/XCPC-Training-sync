#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.03.06 22:40

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>pa = a;
    for(int i = 1;i < n;i++){
        pa[i] = min(a[i], pa[i - 1]);
    }
    vector<vector<int>>g(n);
    for(int i = 0; i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    //rmq?
    int len = __lg(n) + 1;
    vector<vector<int>>st(len, vector<int>(n));
    for(int i = 0;i < n;i++){
        st[0][i] = a[i];
    }
    for(int j = 1;j < len;j++){
        for(int i = 0;i + (1 << j) - 1 < n;i++){
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
        }
    }

    auto rmq = [&](int l, int r)->int
    {
        int le = r - l + 1;
        int k = __lg(le); 
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    };

    vector<int>fa(n, -1), hson(n, -1), sz(n, 1), dep(n), top(n);

    auto dfs1 = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dep[s] = dep[p] + 1;
                self(self, s);
                if(hson[p] == -1 || sz[s] > sz[hson[p]]){
                    hson[p] = s;
                }
                sz[p] += sz[s];
            }
        }
        return;
    };

    dfs1(dfs1, 0);

    auto dfs2 = [&](auto&&self, int p, vector<int>&dp)->void
    {
        dp.push_back(pa[dep[p] - dep[top[p]]]);
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            self(self, hson[p], dp);
        }
        for(auto s : g[p]){
            if(s != fa[p] && s != hson[p]){
                vector<int>sdp;
                top[s] = s;
                self(self, s, sdp);
                int d = dep[s] - dep[top[p]];
                for(int i = 0;i < sdp.size();i++){
                    if(d + i >= dp.size()){
                        dp.push_back(0);
                    }
                    dp[d + i] = min(dp[d + i] + sdp[i], rmq(i + 1, i + d));
                }
            }
        }
        return;
    };

    vector<int>dp;
    dfs2(dfs2, 0, dp);
    i64 ans = 0;
    for(int i = 0;i < dp.size();i++){
        ans += dp[i];
    }
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