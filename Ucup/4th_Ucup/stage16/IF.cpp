#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

struct DSU{
    int n;
    vector<int>fa,sz;
    int scc;

    DSU(int n_) : n(n_),fa(n),sz(n, 1), scc(n)
    {
        iota(fa.begin(),fa.end(), 0);
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    void merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)return;
        if(sz[fu] < sz[fv])swap(fu, fv);
        sz[fu] += sz[fv];
        fa[fv] = fu;
        scc--;
        return;
    }

    void print()
    {
        cerr << "scc = " << scc << endl;
        vector<vector<int>>a(scc);
        vector<int>rtid(n, -1);
        int tot = 0;
        for(int i = 0;i < n;i++){
            if(find(i) == i){
                rtid[i] = tot++;
            }
        }
        for(int i = 0;i < n;i++){
            a[rtid[find(i)]].push_back(i);
        }
        for(int i = 0;i < scc;i++){
            cerr << "set " << i << " : ";
            for(auto x : a[i]){
                cerr << x + 1 << " ";
            }
            cerr << endl;
        }
    }
};

void solve()
{
    int n, m, p;
    cin >> n >> m >> p;
    DSU dsu(n);
    for(int i = 0;i < m;i++){
        int x;
        cin >> x;
        for(int j = 0;j * 2 < x;j++){
            dsu.merge(j, x - j - 1);
        }
    }
    dsu.print();
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}