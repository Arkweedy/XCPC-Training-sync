#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
//template<>
//int MInt<0>::Mod = 998244353;
//int MInt<0>::Mod = 1000000007;
constexpr int P = 998244353;
//constexpr int P = 1000000007;
using Z = MInt<P>;

struct VDCC {
    int n;
    vector<vector<int>> ver, col;
    vector<int> dfn, low, s;
    int now, cnt;
    vector<int> point;  // 是否为割点

    VDCC(int n) { init(n); }

    void init(int n) {
        this->n = n;
        ver.resize(n, {});
        dfn.resize(n, -1);
        low.resize(n, -1);
        col.resize(n, {});
        point.resize(n, 0);
        s.clear();
        cnt = now = 0;
    }

    void add(int x, int y) {
        ver[x].push_back(y);
        ver[y].push_back(x);
    }

    void tarjan(int x, int root) {
        low[x] = dfn[x] = now++;
        s.push_back(x);
        if (x == root && !ver[x].size()) {
            col[cnt++].push_back(x);
            return;
        }

        int flg = 0;
        for (auto y : ver[x]) {
            if (dfn[y] == -1) {
                tarjan(y, root);

                low[x] = min(low[x], low[y]);

                if (dfn[x] <= low[y]) {
                    flg++;
                    if (x != root || flg > 1) {
                        point[x] = 1;
                    }
                    int pre = 0;
                    do {
                        pre = s.back();
                        col[cnt].push_back(pre);
                        s.pop_back();
                    } while (pre != y);
                    col[cnt++].push_back(x);
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }

    void build() {
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1) tarjan(i, i);
    }
};

struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
    
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
    
    int intersection(int x, int y, int u, int v)
    {
        vector<int>t = {lca(x, u), lca(x, v), lca(y, u), lca(y, v)};
        sort(t.begin(), t.end());
        int l = lca(x, y), r = lca(u, v);
        if (dep[l] > dep[r])swap(l, r);
        if (dep[t[0]] < dep[l] || dep[t[2]] < dep[r]) {
            return 0;
        }
        return 1 + dist(t[2], t[3]);
    }
};

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

class exDSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
    

public:
    int scc;

    exDSU(int n)
    {
        init(n);
    }

    exDSU() = default;

    void init(int _n)
    {
        this->n = _n;
        scc = n * 2;
        fa.resize(n * 2);
        sz.resize(n * 2);
        for (int i = 0; i < n * 2; i++) {
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

    bool isBinary()
    {
        return !same(0,n);
    }

    void Mer(int u, int v)
    {
        merge(u, v + n);
        merge(v, u + n);
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
    int n, m, V;
    cin>>n>>m>>V;
    VDCC vb(n);
    vector<vector<int>>g(n);
    vector<int>val(n);
    for(int i = 0;i < n;i++){
        cin>>val[i];
    }

    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
        vb.add(u,v);
    }
    
    vb.build();

    auto& col = vb.col;
    int k = col.size();

    vector<map<int,int>>id(k);
    for(int i = 0;i < k;i++){
        for(int j = 0;j < col[i].size();j++){
            id[i][col[i][j]] = j;
        }
    }

    HLD hld(n + k);

    vector<vector<int>>tr(n + k);
    for(int i = 0;i < k;i++){
        for(auto s : col[i]){
            hld.addEdge(n + i, s);
        }
    }

    hld.work();

    vector<vector<pair<int,int>>>e(k);
    for (int i = 0; i < n; i++) {
        for (auto j : g[i]) {
            if (i < j) {
                int lc = hld.rootedParent(i, j);
                int vcid = lc - n;
                e[lc - n].push_back({id[vcid][i], id[vcid][j] });
            }
        }
    }

    DSU clrdsu(n + 1);
    int zrclr = n;

    for(int i = 0;i < k;i++){
        if(col[i].size() <= 2)continue;
        exDSU dsu(col[i].size());   
        for(auto [u, v] : e[i]){
            dsu.Mer(u, v);
        }
       
        if(dsu.isBinary()){
            
            //binary
            vector<int>buf;
            for(int j = 1;j < col[i].size();j++){
                clrdsu.merge(col[i][j], col[i][0]);
            }
        }
        else{
            //cerr<<"odd circle"<<endl;
            for(auto s : col[i]){
                clrdsu.merge(s, zrclr);
                if(val[s] == 0){
                    continue;
                }
                else if(val[s] == -1){
                    val[s] = 0;
                }
                else{
                    cout<<0<<endl;
                    return;
                }
            }
        }
        
    }

    //scc
    vector<vector<int>>scc(n + 1);
    for(int i = 0;i < n;i++){
        //cerr<<"root : "<<clrdsu.find(i)<<endl;
        scc[clrdsu.find(i)].push_back(i);
    }

    Z ans = 1;
    for(int i = 0;i < n + 1;i++){
        
        if(scc[i].empty())continue;
        int v = -1;
        for(auto s : scc[i]){
            if(val[s] == -1)continue;
            else if(v == -1 && val[s] != -1)v = val[s];
            else if(v != -1 && val[s] != -1 && v != val[s]){
                ans = 0;
            }
        }
        if(v == -1){
            ans *= V;
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