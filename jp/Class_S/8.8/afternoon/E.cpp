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
    int n,k;
    cin>>n>>k;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin>>x[i]>>y[i];
    }
    auto dissq = [&](int i, int j)->int
    {
        return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
    };
    vector<array<int,3>>a;
    for(int i = 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            a.push_back({dissq(i,j),i,j});
        }
    }
    sort(a.begin(),a.end());
    DSU dsu(n);
    double ans = 0;
    for(auto [d, u, v] : a){
        if(dsu.scc == k)ans = sqrt(d);
        if(dsu.same(u,v))continue;
        else dsu.merge(u,v);
    }

    cout<<fixed<<setprecision(2)<<ans<<endl;
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