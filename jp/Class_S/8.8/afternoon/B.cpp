#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;

public:
    int scc;

    DSU(int _n)
    {
        n = _n;
        scc = n;
        fa.resize(n);
        sz.resize(n, 1);
        iota(fa.begin(),fa.end(),0);
    }

    int find(int p)
    {
        return p == fa[p] ? p : (fa[p] = find(fa[p]));
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)return false;
        if(sz[fu] < sz[fv])swap(fu,fv);
        sz[fu] += sz[fv];
        fa[fv] = fu;
        scc--;
        return true;
    }

    bool same(int u,int v)
    {
        return find(u) == find(v);
    }
};

void solve()
{
    int n, m;
    cin>>n>>m;
    array<int,3>a;
    vector<array<int,3>>e(m);
    for(int i = 0;i < m;i++){
        cin>>e[i][1]>>e[i][2]>>e[i][0];
    }
    sort(e.begin(),e.end());
    DSU dsu(n + 1);
    ll ans = 0;
    for(int i = 0;i < m;i++){
        auto &[d,u,v] = e[i];
        if(dsu.same(u,v))continue;
        else{
            ans += d;
            dsu.merge(u,v);
        }
    }

    if(dsu.scc == 2){//0 node + (1 ~ n)scc
        cout<<ans<<endl;
    }
    else{
        cout<<"orz"<<endl;
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