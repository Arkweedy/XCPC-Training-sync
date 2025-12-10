#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using i64 = long long;
using uint = unsigned int;

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
        fa.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
        scc = n;
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    int same(int u, int v)
    {
        return find(u) == find(v);
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            scc--;
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            sz[fu] += sz[fv];
            fa[fv] = fu;
            return true;
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<ll>a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<ll>>g(n, vector<ll>(n));
    vector<array<ll, 3>>edge;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
            edge.push_back({ g[i][j],i,j });
        }
    }
    
    DSU dsu(n);
    ll ans = 0;
    sort(edge.begin(), edge.end());
    for (auto &[val, u, v] : edge) {
        if (u == v && a[u] != 1) {
            ans += (a[u] - 1) * val;
            a[u] = 1;
        }
        if (dsu.same(u, v))continue;
        ans += (a[u] + a[v] - 1) * val;
        dsu.merge(u, v);
        a[u] = a[v] = 1;
        if (dsu.scc == 1)break;
    }
    int mi = *min_element(a.begin(), a.end());
    ans += edge[0][0] * (mi - 1);
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--)
        solve();
    return 0;
}