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


void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    vector<vector<int>>g(n);
    for(int i = 0;i < n-1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>c0(n),c1(n);
    vector<vector<Z>>dp(n);

    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        dp[p] = {1};
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                //merge
                int x = dp[p].size(), y = dp[s].size();
                vector<Z>ndp(x + y - 1);
                for(int i = 0;i < x;i++){
                    for(int j = 0;j < y;j++){
                        ndp[i + j] += dp[p][i] * dp[s][j];
                    }
                }
                dp[p] = move(ndp);
                c0[p] += c0[s];
                c1[p] += c1[s];
            }
        }
        //add self match
        if(s[p] == '0'){
            c0[p]++;
            dp[p].emplace_back();
            for(int i = dp[p].size() - 1;i >= 1;i--){
                dp[p][i] += dp[p][i - 1] * (c1[p] - i + 1);
            }
        }
        else{
            c1[p]++;
            dp[p].emplace_back();
            for(int i = dp[p].size() - 1;i >= 1;i--){
                dp[p][i] += dp[p][i - 1] * (c0[p] - i + 1);
            }
        }
        while(dp[p].back() == 0)dp[p].pop_back();
        return;
    };

    dfs(dfs, 0, -1);


    auto F = dp[0];
    F.resize(n / 2 + 1);
    vector<Z>fac(n / 2 + 1);
    fac[0] = 1;
    for(int i = 1;i <= n / 2;i++){
        fac[i] = fac[i - 1] * i;
    }
    for(int i = 0;i <= n / 2;i++){
        F[i] *= fac[n / 2 - i];//free match
    }
    vector<Z>G(n / 2 + 1);

    for(int i = 0;i <= n / 2;i++){
        int sign = 1;
        for(int j = i;j <= n / 2;j++){
            G[i] += ((j - i) % 2 == 1 ? -1 : 1) * comb.binom(j, i) * F[j];
        }
    }

    for(int i = 0;i <= n / 2 ;i++){
        cout<<G[i]<<endl;
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