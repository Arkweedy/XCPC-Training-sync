#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using i64 = long long;

using namespace std;

class DSU
{
    int n;
    vector<int>fa;
    //vector<int>sz;

public:
    DSU(int n)
    {
        this->n = n;
        fa.resize(n);
        //sz.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            //sz[i] = 1;
        }
    }

    int find(int p)
    {
        return fa[p] == p ?  p : (fa[p] = find(fa[p]));
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            //if (sz[fu] < sz[fv]) {
            //    swap(fu, fv);
            //}
            //sz[fu] += sz[fv];
            fa[fv] = fu;
            return true;
        }
    }
};

template <typename T, bool isMaxQuery>//if 1 base, set arr[0] to inf / -inf . std::max/min override
class rmq
{
    int n;//array length
    int len;//st table length
    vector<vector<T>>stt;//st_table

    T choose(const T& a, const T& b)const
    {
        if constexpr (isMaxQuery) {
            return std::max(a, b);
        }
        else {
            return std::min(a, b);
        }
    }

    void build(vector<T>& arr)
    {
        //build
        for (int i = 0; i < n; i++) {
            stt[i][0] = arr[i];
        }
        for (int k = 1; k < len; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                stt[i][k] = choose(stt[i][k - 1], stt[i + (1 << (k - 1))][k - 1]);
            }
        }
    }

public:
    rmq() = default;

    void late_init(vector<T>& arr)
    {
        n = arr.size();
        len = floor(log2l(n)) + 1;
        stt.resize(n, vector<T>(len));

        build(arr);

    }

    rmq(vector<T>& arr)
    {
        n = arr.size();
        len = floor(log2l(n)) + 1;
        stt.resize(n, vector<T>(len));

        build(arr);
    }

    T qry(int l, int r)
    {
        int k = floor(log2(r - l + 1));// range_len == r - l + 1
        return choose(stt[l][k], stt[r - (1 << k) + 1][k]);
    }
};

class fast_lca
{
protected:
    int n;//g size
    int root;
    vector<vector<int>>g;
    vector<int>dfn;
    vector<int>rnk;
    vector<int>fir;
    vector<int>elr_ord;
    vector<int>dep;
    rmq<int, false>Euler; // range min is lca 
    static constexpr int no_fa = -1;

    int dfn_tmp;

    void dfs(int p, int fa)
    {
        dfn[p] = dfn_tmp;
        rnk[dfn_tmp] = p;
        elr_ord.push_back(dfn[p]);
        fir[p] = elr_ord.size() - 1;

        dfn_tmp++;
        for (auto s : g[p]) {
            if (s != fa) {
                dep[s] = dep[p] + 1;
                dfs(s, p);
                elr_ord.push_back(dfn[p]);
            }
        }
    }

public:
    fast_lca(const vector<vector<int>>& G, int root = 1)//default root 1
    {
        n = G.size();
        this->g = G;
        this->root = root;
        dfn.resize(n);
        rnk.resize(n);
        fir.resize(n);
        dep.resize(n, 1);
        elr_ord.reserve(n * 2);
        dfn_tmp = 0;
        dfs(root, no_fa);
        Euler.late_init(elr_ord);
    }



    int lca(int u, int v)
    {
        if (fir[u] > fir[v]) swap(u, v);
        return rnk[Euler.qry(fir[u], fir[v])];
    }
};




void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>h(n, vector<int>(m));
    vector<int>val(n * m * 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
            val[i * m + j] = h[i][j];
        }
    }
    priority_queue<array<int, 3>>pq;//w,u,v
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            pq.push({ min(h[i][j], h[i][j + 1]), i * m + j, i * m + j + 1 });
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            pq.push({ min(h[i][j], h[i + 1][j]), i * m + j, (i + 1) * m + j });
        }
    }

    int id = n * m;
    DSU dsu(n * m * 2);
    vector<vector<int>>g(n * m * 2);
    
    auto addedge = [&](int u, int v)
        {
            g[u].push_back(v);
            g[v].push_back(u);
        };
    for (int i = 0; i < n * m - 1; i++) {
        int u = -1, v = -1;
        while (1) {
            auto [w, a, b] = pq.top();
            pq.pop();
            if (dsu.find(a) != dsu.find(b)) {
                u = dsu.find(a);
                v = dsu.find(b);
                val[id] = w;
                dsu.merge(id, u);//u->id
                dsu.merge(id, v);
                addedge(u, id);
                addedge(v, id);
                id++;
                break;
            }
        }
    }
    fast_lca t(g, n * m * 2 - 2);
    //tcp t(g, n * m * 2 - 2);
    int q;
    cin >> q;
    while (q--) {
        int a, b, y, c, d, z;
        cin >> a >> b >> y >> c >> d >> z;
        a--, b--, c--, d--;
        int low = val[t.lca(a * m + b, c * m + d)];
        if (low < y && low < z) {
            cout << y + z - low * 2 << endl;
        }
        else {
            cout << abs(y - z) << endl;
        }
    }
    return;


}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

        solve();
    return 0;
}
