#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.17 21:19:30

void solve()
{
    int n;
    cin >> n;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>fa(n, -1), deg(n);
    [&](this auto&&dfs, int p)->void
    {
        for(auto s : g[p]){
            if(s != p){
                deg[p]++;
                fa[s] = p;
                dfs(s);
            }
        }
        return;
    }(0);

    priority_queue<pair<i64,int>>pq;
    for(int i = 1;i < n;i++){
        if(deg[i] == 0){
            pq.push({a[i], i});
        }
    }

    while(!pq.empty()){
        auto [v, p] = pq.top();
        pq.pop();
        int q = fa[p];
        a[q] -= a[p];
        deg[q]--;
        if(deg[q] == 0){
            pq.push({a[q], q});
        }
    }

    i64 ans = a[0];

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