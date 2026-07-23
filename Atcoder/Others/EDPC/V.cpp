#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.16 16:52:50

void solve()
{
    int n, m;
    cin >> n >> m; 
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<array<int,2>>dp(n, array<int, 2>{1, 1});

    //0 : self 0, sub 0 
    //1 : self 1, sub 1
    //2 : self 0, sub 1
    [&](this auto&&dfs, int p, int fa)->void
    {
        for(auto s : g[p]){
            if(s != fa){
                dfs(s, p);
                dp[p][0] = 1ll * dp[p][0] * dp[s][0] % m;
                dp[p][1] = 1ll * dp[p][1] * (dp[s][1] + dp[s][0]) % m;
                //dp[p][2] = 1ll * dp[p][2] * (0ll + dp[s][0] + dp[s][1] + dp[s][2]) % m;
            }
        }
        //dp[p][2] = (dp[p][2] - dp[p][0] + m) % m;
    }(0, -1);

    vector<array<int, 2>>rdp(n, array<int, 2>{1, 1});

    [&](this auto&&rdfs, int p, int fa)->void
    {
        vector<int>pre0, suf0;
        vector<int>pre01, suf01;
        vector<int>son;
        for(auto s : g[p]){
            if(s != fa){
                son.push_back(s);
                pre0.push_back(dp[s][0]);
                pre01.push_back((dp[s][0] + dp[s][1]) % m);
                suf0.push_back(dp[s][0]);
                suf01.push_back((dp[s][0] + dp[s][1]) % m);
            }
        }
        int sz = son.size();
        for(int i = 1;i < sz;i++){
            pre0[i] = 1ll * pre0[i] * pre0[i - 1] % m;
            pre01[i] = 1ll * pre01[i] * pre01[i - 1] % m;
        }
        for(int i = sz - 2;i >= 0;i--){
            suf0[i] = 1ll * suf0[i] * suf0[i + 1] % m;
            suf01[i] = 1ll * suf01[i] * suf01[i + 1] % m;
        }
        for(int i = 0;i < sz;i++){
            int x = rdp[p][0], y = rdp[p][1];
            if(i > 0){
                x = 1ll * x * pre0[i - 1] % m; 
                y = 1ll * y * pre01[i - 1] % m; 
            }
            if(i < sz - 1){
                x = 1ll * x * suf0[i + 1] % m; 
                y = 1ll * y * suf01[i + 1] % m; 
            }
            rdp[son[i]][0] = 1ll * rdp[son[i]][0] * x % m;
            rdp[son[i]][1] = 1ll * rdp[son[i]][1] * (x + y) % m;
        }
        if(sz > 0){
            rdp[p][0] = 1ll * rdp[p][0] * suf0[0] % m;
            rdp[p][1] = 1ll * rdp[p][1] * suf01[0] % m;
        }
        for(auto s : g[p]){
            if(s != fa){
                rdfs(s, p);
            }
        }
    }(0, -1);

    for(int i = 0;i < n;i++){
        cout << rdp[i][1] << "\n";
    }
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