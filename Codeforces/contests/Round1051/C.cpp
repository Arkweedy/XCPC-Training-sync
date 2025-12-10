#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    vector<int>indeg(n);
    for(int i = 0;i < n - 1;i++){
        int u,v,x,y;
        cin>>u>>v>>x>>y;
        u--,v--;
        if(x > y)g[u].push_back(v),indeg[v]++;
        else g[v].push_back(u),indeg[u]++;
    }

    int tot = 1;
    vector<int>val(n);
    vector<int>vs(n);
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        if(vs[p])return;
        vs[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                self(self, s ,p);
            }
        }
        val[p] = tot++;
    };

    for(int i = 0;i < n;i++){
        if(indeg[i] == 0){
            dfs(dfs, i, -1);
        }
    }

    for(int i = 0;i < n;i++){
        cout<<val[i]<<" ";
    }
    cout<<endl;
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