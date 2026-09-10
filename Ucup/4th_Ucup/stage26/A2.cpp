#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A2.cpp Create time : 2026.07.26 15:32

struct DSU{
    int n;
    vector<int>fa,sz,clr;
    
    DSU(int n_, vector<int>a)
    {
        n = n_;
        fa.resize(n);
        iota(fa.begin(),fa.end(),0);
        sz.resize(n, 1);
        clr.resize(n, -1);
        for(int i = 0;i < a.size();i++){
            clr[a[i]] = i;
        }
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    void merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)return;
        if(clr[fu] != -1 && clr[fv] != -1 && clr[fu] != clr[fv])return;
        if(sz[fu] < sz[fv])swap(fu, fv);
        fa[fv] = fu;
        sz[fu] += fv;
        clr[fu] = max(clr[fu], clr[fv]);
    }

    int get(int p)
    {
        return clr[find(p)];
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(m), b(n, -1);
    for(int i = 0;i < m;i++){
        cin >> a[i];
        a[i]--;
        b[a[i]] = i;
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n- 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    

    DSU dsu(n, a);
    vector<int>st(n);
    int ok = 1;
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        if(b[p] == -1){
            st[p] = 0;
        }
        else{
            st[p] = 1;
        }
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                if(st[p] == 0){
                    if(st[s] == 0){
                        dsu.merge(s, p);
                    }
                    else if(st[s] == 1){
                        dsu.merge(s, p);
                        st[p] = 2;
                    }
                    else if(st[s] == 2){
                        //
                    }
                }   
                else if(st[p] == 1){
                    if(st[s] == 0){
                        dsu.merge(s, p);
                        st[p] = 2;
                    }
                    else if(st[s] == 1){
                        ok = 0;
                    }
                    else{
                        //
                    }
                }
                else if(st[p] == 2){
                    if(st[s] == 0){
                        dsu.merge(s, p);
                    }
                    else if(st[s] == 1){
                        ok = 0;
                    }
                    else{
                        //
                    }
                }
            }
        }
        return;
    };

    dfs(dfs, 0, -1);
    if(st[0] == 1 && n != 1)ok = 0;
    if(ok){
       
        if(dsu.get(0) == -1){
            auto fx = [&](auto&&self, int p, int fa)->int
            {
                if(dsu.get(p) != -1)return p;
                for(auto s : g[p]){
                    if(s != fa){
                        int res = self(self, s, p);
                        if(res != -1)return res;
                    }
                }
                return -1;
            };
            int np = fx(fx, 0, -1);
            dsu.merge(0, np);
        }
        cout << "YES\n";
        for(int i = 0;i < n;i++){
            cout << dsu.get(i) + 1 << " ";
        }
        cout << "\n";
    }
    else{
        cout << "NO\n";
    }
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