#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.04.03 16:12:02
struct EBCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    EBCC() {}
    EBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        int num=0;
        for (auto y : adj[x]) {
            if (y == p) {
                if(!num) num++;
                else low[x]=std::min(low[x],dfn[p]);
                continue;
            }
            if (dfn[y] == -1) {
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1 && dfn[y] < dfn[x]) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    std::vector<int> build() {
        for(int i=0;i<n;i++)
            if(dfn[i]==-1) dfs(i,-1);
        return bel;
    }
};

constexpr int P = 998244353;

int power(int a, int p)
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
    int n, m;
    cin >> n >> m;
    EBCC ebcc(n);
    vector<pair<int, int>>e;
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        ebcc.add(u, v);
        e.emplace_back(u, v);
    }
    ebcc.build();
    int en = ebcc.cnt;
    vector<vector<int>>g(en);
    vector<int>sz(en);
    vector<int>incnt(en);
    auto&bel = ebcc.bel;
    for(int i = 0;i < n;i++){
        sz[bel[i]]++;
    }
    for(auto [u, v] : e){
        int x = bel[u], y = bel[v];
        if(x != y){
            g[x].push_back(y);
            g[y].push_back(x);
        }
        else{
            incnt[x]++;
        }
    }
    vector<int>p2(n * n + 1);
    p2[0] = 1;
    for(int i = 1;i <= n * n;i++){
        p2[i] = p2[i - 1] * 2 % P;
    }
    vector<vector<int>>dp(en);
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        dp[p].resize(sz[p] + 1);
        dp[p][sz[p]] = p2[sz[p] * (sz[p] - 1) / 2 - incnt[p]];
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                int x = dp[p].size(), y = dp[s].size();
                vector<int>ndp(x + y - 1);
                for(int i = 1;i < x;i++){
                    for(int j = 1;j < y;j++){
                        ndp[i + j] = (ndp[i + j] + 1ll * dp[p][i] * dp[s][j] % P * p2[i * j - 1]) % P;
                        ndp[i] = (ndp[i] - 1ll * dp[p][i] * dp[s][j] % P + P) % P;
                    }
                }
                dp[p] = move(ndp);
            }
        }
    };

    dfs(dfs, 0, -1);
    int ans = 0;
    for(int i = 0;i <= n;i++){
        ans = (ans + dp[0][i]) % P;
    }
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