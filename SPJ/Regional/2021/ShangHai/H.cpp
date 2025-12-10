#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

class DSU
{
public:
    int n;
    vector<int>fa;

    DSU(int _n)
    {
        n = _n;
        fa.resize(n);
        iota(fa.begin(),fa.end(), 0);
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)return false;
        fa[fv] = fu;
        return true;
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }
};

void solve()
{
    int n, m , q;
    cin>>n>>m>>q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<array<int,3>>e;
    for(int i = 0;i < m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        e.push_back({w,u,v});
    }

    sort(e.begin(),e.end());
    vector<vector<int>>g(n * 2);//kruskal
    vector<int>fa(n * 2, n * 2 - 2);
    vector<int>val(n * 2);//value on kruskal
    
    DSU dsu(n * 2);
    int tot = n;
    for(auto [w,u,v] : e){
        if(!dsu.same(u,v)){
            u = dsu.find(u), v = dsu.find(v);
            dsu.merge(tot,u);
            dsu.merge(tot,v);
            g[tot].push_back(u);
            g[tot].push_back(v);
            fa[u] = fa[v] = tot;
            val[tot] = w;
            tot++;
        }
    }

    
    constexpr int inf = 2e9;
    vector<int>con(n * 2), sum(n * 2);
    //prefix min
    for(int i = 0;i < n;i++){
        sum[i] = a[i];
    }

    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            //if(s != fa[p]){
                self(self, s);
                sum[p] += sum[s];
            //}
        }
        con[p] = sum[p] - val[fa[p]];
    };

    dfs(dfs, tot - 1);
    int all = n * 2 - 1;
    //cerr<<all<<" "<<tot<<endl;
    assert(all == tot);
    int len = __lg(all) + 1;
    vector<vector<int>>mi(all, vector<int>(len, -inf));
    vector<vector<int>>f(all, vector<int>(len));

    //con[tot-1] = -inf;

    for(int i = 0;i < all;i++){
        mi[i][0] = con[i];
        f[i][0] = fa[i];
    }


    for(int j = 1;j < len;j++){
        for(int i = 0;i < tot;i++){
            f[i][j] = f[f[i][j - 1]][j - 1];
            mi[i][j] = min(mi[i][j - 1], mi[f[i][j - 1]][j - 1]);
        }
    }



    while(q--){
        int p, k;
        cin>>p>>k;
        p--;
        for(int i = len - 1;i >= 0;i--){
            if(k + mi[p][i] >= 0){
                p = f[p][i];
            }
        }

        int ans = k + sum[p];
        cout<<ans<<"\n";
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}