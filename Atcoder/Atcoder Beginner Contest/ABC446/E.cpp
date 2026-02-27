#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.21 20:20

// think in mod M
// fn = afn-1+bfn-2

void solve()
{
    int m, a, b;
    cin >> m >> a >> b;
    int n = m * m;
    
    vector<vector<int>>rg(n);
    for(int i = 0;i < m;i++){
        for(int j = 0;j < m;j++){
            int k = (a * i + b * j) % m;
            //cerr << k * m + i << " " << i * m + j << endl;
            rg[k * m + i].push_back(i * m + j);
        }
    }

    vector<int>ok(n, 1);
    auto dfs = [&](auto&&self, int p)->void
    {
        if(!ok[p])return;
        ok[p] = 0;
        for(auto s : rg[p]){
            self(self, s);
        }
    };

    for(int i = 0;i < m;i++){
        int u = i, v = i * m;
        dfs(dfs, u);
        dfs(dfs, v);
    }

    int ans = count(ok.begin(),ok.end(), 1);
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