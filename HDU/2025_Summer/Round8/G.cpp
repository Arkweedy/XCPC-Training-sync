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


void solve()
{
    
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