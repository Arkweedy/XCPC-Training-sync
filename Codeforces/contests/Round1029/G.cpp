#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int inf = 1e9 + 7;

class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
    vector<ll>mi;
    vector<ll>ma;
    

public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
        mi.resize(n,inf);
        ma.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    int size(int p)
    {
        return sz[find(p)];
    }

    bool merge(int u, int v, ll w)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            scc--;
            sz[fu] += sz[fv];
            fa[fv] = fu;
            ma[fu] = max(w,max(ma[fu],ma[fv]));
            mi[fu] = min(w,min(mi[fu],mi[fv]));
            return true;
        }
    }

    ll get()
    {
        return mi[find(0)] + ma[find(0)];
    }
};

void solve()
{
    int n, m;
    cin>>n >> m;
    vector<array<int, 3>>e(m);
    for(int i = 0;i < m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        e[i] = {w,u,v};
    }
    sort(e.begin(),e.end());
    DSU dsu(n);
    ll ans = LLONG_MAX;
    for(int i = 0; i< m;i++){
        auto [w,u,v] = e[i];
        dsu.merge(u,v,w);
        if(dsu.same(0,n-1)){
            ans = min(ans,dsu.get());
        }
    }
    cout<<ans<<endl;
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