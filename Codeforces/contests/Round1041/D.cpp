#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
constexpr T power(T a, i64 b) {
    T res {1};
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
 
template<i64 P>
struct MInt {
    i64 x;
    constexpr MInt() : x {0} {}
    constexpr MInt(i64 x) : x {norm(x % getMod())} {}
     
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
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
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};
 
//constexpr int P = 998244353;
constexpr int P = 1000000007;
using Z = MInt<P>;

struct Comb {
    int n;
    vector<Z> _fac;
    vector<Z> _invfac;
    vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }

    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
        
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

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
    int n,m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    vector<int>clr(n, -1);
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int neg = 0;
    vector<int>vs(n);
    auto dfs1 = [&](auto&&self, int p, int fa)->void
    {
        vs[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                if(!vs[s]){
                    clr[s] = clr[p] ^ 1;
                    self(self, s , p);
                }
                else{
                    if(clr[s] ^ clr[p] == 0){
                        neg = 1;
                        return;
                    }
                }
            }
        }
    };
    int root = 0;
    clr[root] = 0;
    dfs1(dfs1, root, -1);
    if(neg){
        cout<<0<<endl;
        return;
    }

    vector<int>degnleaf(n);
    for(int i = 0;i < n;i++){
        for(auto s : g[i]){
            if(g[s].size() > 1)degnleaf[i]++;
        }
    }

    vs.assign(n,0);
    DSU dsu(n);
    Z ans = 1;
    auto dfs2 = [&](auto&&self ,int p,int fa)->void
    {
        int cnt = 0;
        int leaf = 0;
        vs[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                if(vs[s]){
                    neg = 1;
                    return;
                }
                if(g[s].size() > 1)cnt++;
                else leaf++;
                dsu.merge(s, p);
                self(self, s, p);
            }
        }
        if(cnt >= 2)neg = 1;
        if(leaf >= 2)ans *= comb.fac(leaf);
    };

    auto dfs3 = [&](auto&&self ,int p,int fa)->void
    {
        int cnt = 0;
        int leaf = 0;
        vs[p] = 1;
        for(auto s : g[p]){
            if(s != fa){
                if(vs[s]){
                    neg = 1;
                    return;
                }
                if(g[s].size() > 1)cnt++;
                else leaf++;
                dsu.merge(s, p);
                self(self, s, p);
            }
        }
        if(cnt >= 2)neg = 1;
    };

    int res = 0;
    for(int i = 0;i < n;i++){
        //从链端进去
        if(!vs[i] && degnleaf[i] == 1 && g[i].size() >= 2){
            res++;
            dfs2(dfs2,i,-1);
        }
    }

    for(int i = 0;i < n;i++){
        //剩下的随便进
        //菊花
        if(!vs[i]){
            res++;
            dfs3(dfs3,i,-1);
            ans *= comb.fac(dsu.size(i) - 1);
        }
    }

    if(count(vs.begin(),vs.end(),1) != n){
        neg = 1;
    }

    vector<int>bone(n);//计算骨架点数
    for(int i = 0;i < n;i++){
        if(g[i].size() > 1){
            bone[dsu.find(i)]++;
            if(degnleaf[i] == 1)bone[dsu.find(i)]++;
        }
    }
    
    if(neg){
        cout<<0<<endl;
        return;
    }
    else{
        ans *= comb.fac(res);
        for(int i = 0;i < n;i++){
            if(i == dsu.find(i)){
                cerr<<bone[i]<<endl;
                if(bone[i] >= 3)ans *= 4;
                else if(dsu.size(i) >= 2)ans *= 2;
            }
        }
        cout<<ans<<endl;
        return;
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