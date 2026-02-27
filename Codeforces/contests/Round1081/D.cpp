#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.21 23:14

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n- 1;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<i64>dep(n), sum(n), val(n), more(n);
    vector<i64>ans(n);

    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        
        vector<int>son;
        i64 res = 0;
        val[p] = a[p];
        sum[p] = a[p];
        dep[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                son.push_back(s);
                res += val[s];
                sum[p] += sum[s];
                val[p] += sum[s] + val[s];
                dep[p] = max(dep[p], dep[s] + 1);
                more[p] = max(more[p], more[s]);
            }
        }
        int m = son.size();
        vector<int>idd(m), ids(m);
        iota(idd.begin(),idd.end(), 0);
        iota(ids.begin(),ids.end(), 0);
        sort(idd.begin(),idd.end(), [&](int i, int j)->bool
        {
            return dep[son[i]] > dep[son[j]];
        });
        sort(ids.begin(),ids.end(), [&](int i, int j)->bool
        {
            return sum[son[i]] > sum[son[j]];
        });

        if(m >= 1){
            if(idd[0] == ids[0]){
                more[p] = max(more[p], max(dep[son[idd[1]]] * sum[son[ids[0]]], dep[son[idd[0]]] * sum[son[ids[1]]]));
            }
            else{
                more[p] = max(more[p], dep[son[idd[0]]] * sum[son[ids[0]]]);
            }
            
        }
        res += more[p];
        ans[p] = res;
    };

    dfs(dfs, 0, -1);
    for(int i = 0;i < n;i++){

        cout << ans[i] << " ";
    }
    cout << endl;
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