#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//Whalica1.cpp Create time : 2026.02.17 01:41

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int no = 0;
    vector<int>ok(n);
    vector<int>dp(n);
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        vector<int>b, c;//ok, a list to up
        int oma = 0;//ok's list max
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                if(ok[s]){
                    b.push_back(s);
                    oma = max(oma, dp[s]);
                }
                else c.push_back(s);
            }
        }

        if(c.size() == 0){
            dp[p] = a[p] + oma;
            if(dp[p] >= k)ok[p] = 1;
        }
        else if(c.size() == 1){
            dp[p] = a[p] + dp[c[0]];
            if(dp[p] >= k)ok[p] = 1;
            else if(dp[p] + oma >= k)ok[p] = 1;
        }
        else if(c.size() == 2){
            if(a[p] + dp[c[0]] + dp[c[1]] >= k)ok[p] = 1;
            else no = 1;
        }
        else{
            no = 1;
        }
        return;
    };

    dfs(dfs, 0, -1);
    for(int i = 0;i < n;i++){
        cerr << ok[i] << " ";
    }
    cerr << endl;
    for(int i = 0;i < n;i++){
        cerr << dp[i] << " ";
    }
    cerr << endl;

    if(!no && ok[0]){
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
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}