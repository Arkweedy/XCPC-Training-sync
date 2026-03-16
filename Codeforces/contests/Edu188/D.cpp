#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.16 22:53:21

// bi -graph

void solve()
{
    int n , m;
    cin >> n >> m;
    vector<vector<int>>g(n);
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 


    vector<int>clr(n, -1), vs(n);
    auto dfs = [&](auto&&self, int p, int& l, int& r)->bool
    {
        //cerr << "vs " << p << endl;
        vs[p] = 1;
        if(clr[p] == 0)l++;
        else if(clr[p] == 1)r++;
        int ok = 1;
        for(auto s : g[p]){
            if(!vs[s]){
                clr[s] = (clr[p] ^ 1);
                if(!self(self, s, l, r)){
                    ok = 0;
                }
            }
            else{
                if((clr[p] ^ clr[s]) == 0)ok = 0;
            }
        }
        return ok;
    };

    int ans = 0;
    for(int i = 0;i < n;i++){
        if(!vs[i]){
            clr[i] = 0;
            int l = 0, r = 0;
            int ok = dfs(dfs, i, l, r);
            if(ok)ans += max(l, r);
        }
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