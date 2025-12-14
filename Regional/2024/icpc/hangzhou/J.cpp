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


Z binom(int n ,int m)
{
    if(m == 0)return 1;
    if(m > n || m < 0)return 0;
    Z res = 1;
    for(int i = 0;i < m;i++){
        res *= (n - i);
    }
    res *= comb.invfac(m);
    return res;
}

void solve()
{
    int n1,n2,m,k;
    cin>>n1>>n2>>m>>k;
    vector<pair<int,int>>con(k);
    vector<int>vs(m);
    for(int i = 0;i < k;i++){
        cin>>con[i].first>>con[i].second;
        con[i].first--;
        con[i].second--;
        vs[con[i].first] = vs[con[i].second] = 1;
    }
    int len = count(vs.begin(),vs.end(),1);
    int sz = 1 << len;
    int free = m - len;
    int tot = 0;
    int mask = (1 << len) - 1;
    vector<int>id(m,-1);
    for(int i = 0;i < m;i++){
        if(vs[i])id[i] = tot++;
    }
    vector<Z>val1(sz),val2(sz);
    vector<int>ne(len);
    for(int i = 0;i < k;i++){
        ne[id[con[i].first]] |= 1 << id[con[i].second];
        ne[id[con[i].second]] |= 1 << id[con[i].first];
    }
    for(int i = 0;i < sz;i++){
        val1[i] = binom(n1 + free - 1, len - __popcount(i) - 1 + free);
        val2[i] = binom(n2 + free - 1, len - __popcount(i) - 1 + free);
        for(int j = 0;j < len;j++){
            if((i >> j & 1) && (i & ne[j]) != 0){
                val1[i] = val2[i] = 0;
                break;
            }
        }
    }
    auto sosval = val2;
    for(int i = 0;i < len;i++){
        for(int j = 0;j < sz;j++){
            if(j >> i & 1){
                sosval[j] += sosval[j ^ (1 << i)];
            }
        }
    }

    Z ans = 0;
    
    for(int i = 0;i < sz;i++){
        ans += val1[i] * sosval[i^mask];
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