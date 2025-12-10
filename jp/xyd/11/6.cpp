#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>dep(n);
    constexpr int inf = 1145141919;
    int ans = inf;
    vector<int>vs(n);
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        vs[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                if(vs[s]){//is ancestor or visited son
                    ans = min(ans, abs(dep[p] - dep[s]) + 1);
                }
                else{
                    dep[s] = dep[p] + 1;
                    self(self, s, p);
                }
            }
        }
        return;
    };
    
    for(int i = 0;i < n;i++){
        vs.assign(n,0);//ok???
        if(!vs[i]){
            dfs(dfs,i,-1);
        }
    }
    
    if(ans == inf)ans = -1;
    cout<<ans<<endl;
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