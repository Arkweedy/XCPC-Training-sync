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

void solve()
{
    int n, m, k;
    cin>>n>>m>>k;
    vector<vector<int>>g(n);
    vector<int>a(m);
    
    vector<pair<int,int>>e;
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
        e.push_back({u,v});
    }
    map<pair<int,int>,int>mp;
    for(int i = 0;i < m;i++){
        cin>>a[i];
        a[i]--;
        auto [u,v] = e[a[i]];
        mp[{u,v}] = mp[{v,u}] = i;
    }
    
    vector<int>fa(n, -1),sz(n, 1),dep(n),hson(n,-1),top(n),val(n);
    auto dfs1 = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                dep[s] = dep[p] + 1;
                fa[s] = p;
                self(self, s);
                sz[p] += sz[s];
                if(hson[p] == -1 || sz[hson[p]] <= sz[s]){
                    hson[p] = s;
                }
            }
        }
        return;
    };

    auto dfs2 = [&](auto&&self, int p)->void
    {
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            val[hson[p]] = val[p];
            if(mp.count({p,hson[p]})){
                val[hson[p]] |=  1<<mp[{p,hson[p]}];
            }
            
            self(self, hson[p]);
        }

        for(auto s : g[p]){
            if(s != fa[p] && s != hson[p]){
                val[s] = val[p];
                if(mp.count({s,p})){
                    val[s] |= 1<<mp[{s,p}];
                }
                top[s] = s;
                self(self, s);
            }
        }
        return;
    };
    dfs1(dfs1,0);
    dfs2(dfs2,0);
    auto lca = [&](int u, int v)->int
    {
        while(top[u] != top[v]){
            if(dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            }
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };

    auto pathval = [&](int u, int v)->int
    {
        return val[u] ^ val[v];
    };

    int len = 1 << m;
    vector<Z>f(len);
    for(int i = 0;i < k;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        f[pathval(u,v)]+=1;
    }

    auto fmt = [&](vector<Z>&f)->void
    {
        for(int i = 0;i < m;i++){
            for(int j = 0;j < len;j++){
                if(j >> i & 1){
                    f[j] += f[j ^ (1 << i)];
                }
            }
        }
    };

    auto calc_fx = [&](vector<Z>&ff, int x)->Z
    {
        Z res = 0;
        int len = 1 << 31 - __countl_zero(x);
        for(int i = 0;i < len;i++){
            if((i & x) == i){
                res += ff[i] * ((__popcount(x) - __popcount(i)) % 2 == 0 ? 1 : -1);
            }
        }
        return res;
    };

    auto invfac = [&](int x)->Z
    {
        Z res = 1;
        for(int i = 2;i <= x;i++){
            res *= i;
        }
        return 1 / res;
    };

   

    auto fg = f;
    fmt(fg);
    fmt(f);
    
    for(int i = 1;i <= m;i++){
        Z res = calc_fx(fg,len - 1);
        if(res != 0){
            res *= invfac(i);
            cout<<i<<" "<<res<<endl;
            return;
        }
        for(int j = 0;j < len;j++){
            fg[j] *= f[j];
        }
    }
    cout<<-1<<endl;

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