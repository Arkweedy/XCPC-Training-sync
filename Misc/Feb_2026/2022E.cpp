#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//2022E.cpp Create time : 2026.02.18 23:41

class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
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

    bool merge(int u, int v)
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
            return true;
        }
    }
};

//A_ij = ai ^ bj

constexpr int P = 1e9 + 7;

constexpr int N = (1u << 30);

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    int free = n + m - 1;
    set<pair<int,int>>bind;
    vector<int>val(n + m, 0);
    DSU dsu(n + m);
    vector<vector<pair<int,int>>>g(n + m);
    int ok = 1;

    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        for(auto [s, w] : g[p]){
            if(s != fa){
                val[s] = val[p] ^ w;
                self(self, s, p);
            }
        }
        return;
    };

    for(int i = 0;i < k;i++){
        int r, c, v;
        cin >> r >> c >> v;
        r--,c--;

        if(dsu.same(r, c + n)){
            // free eq, check if ok
            if((val[r] ^ val[c + n]) != v){
                ok = 0;
            }
        }
        else{
            g[r].emplace_back(c + n, v);
            g[c + n].emplace_back(r, v);
            int x = dsu.find(r), y = dsu.find(c + n);
            int p = r, q = c + n;
            if(dsu.size(x) < dsu.size(y))swap(p, q);
            val[q] = val[p] ^ v;
            dfs(dfs, q, p);
            dsu.merge(r, c + n);
            free--;
        }
    }
    if(ok){
        cout << power(N, free) << endl;
    }
    else{
        cout << 0 << endl;
    }


    

    while(q--){
        int r, c, v;
        cin >> r >> c >> v;
        r--,c--;

        if(dsu.same(r, c + n)){
            // free eq, check if ok
            if((val[r] ^ val[c + n]) != v){
                ok = 0;
            }
        }
        else{
            g[r].emplace_back(c + n, v);
            g[c + n].emplace_back(r, v);
            int x = dsu.find(r), y = dsu.find(c + n);
            int p = r, q = c + n;
            if(dsu.size(x) < dsu.size(y))swap(p, q);
            val[q] = val[p] ^ v;
            dfs(dfs, q, p);
            dsu.merge(r, c + n);
            free--;
        }
        if(ok){
            cout << power(N, free) << endl;
        }
        else{
            cout << 0 << endl;
        }
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