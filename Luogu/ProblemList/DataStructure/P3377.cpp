#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using u32 = unsigned int;
using uint = unsigned int;
using u64 = unsigned long long;
using ull = unsigned long long;

using namespace std;

//P3377.cpp Create time : 2026.02.06 22:51

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

    bool mergeto(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            sz[fu] += sz[fv];
            fa[fv] = fu;
            return true;
        }
    }
};

using heap = priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<heap>a(n);
    DSU dsu(n);
    vector<int>del(n);
    for(int i = 0; i < n;i++){
        int x;
        cin >> x;
        a[i].emplace(x, i);
    }

    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            int x, y;
            cin >> x >> y;
            x--,y--;
            int px = dsu.find(x), py = dsu.find(y);
            if(del[x] || del[y] || px == py)continue;
            if(a[px].size() < a[py].size())swap(px,py);
            while(!a[py].empty()){
                auto e = a[py].top();
                a[px].push(e);
                a[py].pop();
            }
            dsu.mergeto(px, py);
        }
        else{
            int x;
            cin >> x;
            x--;
            if(del[x]){
                cout << -1 << "\n";
                continue;
            }
            int px = dsu.find(x);
            assert(a[px].size() > 0);
            auto [v, id] = a[px].top();
            cout << v << "\n";
            a[px].pop();
            del[id] = 1;
        }
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