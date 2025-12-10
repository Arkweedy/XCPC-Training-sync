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

vector<Z>& operator*= (vector<Z>&lhs, const vector<Z>& rhs)
{
    int x = lhs.size(), y = rhs.size();
    //lhs.resize(x + y - 1);
    vector<Z>f(x + y - 1);
    for(int i = 0;i < x;i++){
        for(int j = 0;j < y;j++){
            f[i + j] += lhs[i] * rhs[j];
        }
    }
    lhs = move(f);
    return lhs; 
}

void solve()
{
    int n, a, b, c, d;
    cin>>n>>a>>b>>c>>d;
    int mi = min({a,b,c,d,n/4});
    Z ans = 0;
    constexpr int N = 1010;
    vector<Z>invfac(N);
    invfac[0] = 1;
    for(int i = 1;i < N;i++){
        invfac[i] = invfac[i - 1] / i;
    }

    for(int i = 0;i <= mi;i++){
        int m = n - i * 4;
        Z sum = 0;

        vector<Z>va(invfac.begin(), invfac.begin() + a - i + 1);
        vector<Z>vb(invfac.begin(), invfac.begin() + b - i + 1);
        vector<Z>vc(invfac.begin(), invfac.begin() + c - i + 1);
        vector<Z>vd(invfac.begin(), invfac.begin() + d - i + 1);
        vector<Z>v = {1};
        v *= va;
        v *= vb;
        v *= vc;
        v *= vd;
        sum = comb.fac(m) * v[m];

        // int mia = min(m, a - i), mib = min(m, b - i), mic = min(m, c - i), mid = min(m, d - i);
        // for(int x = 0;x <= mia;x++){
        //     for(int y = 0;y <= mib && x + y <= m;y++){
        //         for(int z = max(m - x - y - mid, 0);z <= mic && x + y + z <= m;z++){
        //             sum += comb.fac(m) * comb.invfac(x) * comb.invfac(y) * comb.invfac(z) * comb.invfac(m - x - y - z);
        //         }
        //     }
        // }

        sum *= comb.binom(n - 3 * i, i);
        ans += (i % 2 == 0 ? 1 : -1) * sum;
    }
    cout<<ans<<endl;
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