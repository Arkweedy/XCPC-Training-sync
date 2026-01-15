#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
 
using u128 = unsigned __int128;
using i128 = __int128;
 
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
};
 
template<>
int MInt<0>::Mod = 1;
 
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
 
constexpr int P = 998244353;
using Z = MInt<P>;
 
std::vector<int> rev;
template<int P>
std::vector<MInt<P>> roots{0, 1};
 
template<int P>
constexpr MInt<P> findPrimitiveRoot() {
    MInt<P> i = 2;
    int k = __builtin_ctz(P - 1);
    while (true) {
        if (power(i, (P - 1) / 2) != 1) {
            break;
        }
        i += 1;
    }
    return power(i, (P - 1) >> k);
}
 
template<int P>
constexpr MInt<P> primitiveRoot = findPrimitiveRoot<P>();
 
template<>
constexpr MInt<998244353> primitiveRoot<998244353> {31};
 
template<int P>
constexpr void dft(std::vector<MInt<P>> &a) {
    int n = a.size();
     
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
     
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            std::swap(a[i], a[rev[i]]);
        }
    }
    if (roots<P>.size() < n) {
        int k = __builtin_ctz(roots<P>.size());
        roots<P>.resize(n);
        while ((1 << k) < n) {
            auto e = power(primitiveRoot<P>, 1 << (__builtin_ctz(P - 1) - k - 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots<P>[2 * i] = roots<P>[i];
                roots<P>[2 * i + 1] = roots<P>[i] * e;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                MInt<P> u = a[i + j];
                MInt<P> v = a[i + j + k] * roots<P>[k + j];
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
}
 
template<int P>
constexpr void idft(std::vector<MInt<P>> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    MInt<P> inv = (1 - P) / n;
    for (int i = 0; i < n; i++) {
        a[i] *= inv;
    }
}
 
template<int P = 998244353>
struct Poly : public std::vector<MInt<P>> {
    using Value = MInt<P>;
     
    Poly() : std::vector<Value>() {}
    explicit constexpr Poly(int n) : std::vector<Value>(n) {}
     
    explicit constexpr Poly(const std::vector<Value> &a) : std::vector<Value>(a) {}
    constexpr Poly(const std::initializer_list<Value> &a) : std::vector<Value>(a) {}
     
    template<class InputIt, class = std::_RequireInputIter<InputIt>>
    explicit constexpr Poly(InputIt first, InputIt last) : std::vector<Value>(first, last) {}
     
    template<class F>
    explicit constexpr Poly(int n, F f) : std::vector<Value>(n) {
        for (int i = 0; i < n; i++) {
            (*this)[i] = f(i);
        }
    }
     
    constexpr Poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return Poly();
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }
    constexpr Poly trunc(int k) const {
        Poly f = *this;
        f.resize(k);
        return f;
    }
    constexpr friend Poly operator+(const Poly &a, const Poly &b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
        return res;
    }
    constexpr friend Poly operator-(const Poly &a, const Poly &b) {
        Poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
        return res;
    }
    constexpr friend Poly operator-(const Poly &a) {
        std::vector<Value> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = -a[i];
        }
        return Poly(res);
    }
    constexpr friend Poly operator*(Poly a, Poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        if (a.size() < b.size()) {
            std::swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return c;
        }
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        idft(a);
        a.resize(tot);
        return a;
    }
    constexpr friend Poly operator*(Value a, Poly b) {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }
    constexpr friend Poly operator*(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }
    constexpr friend Poly operator/(Poly a, Value b) {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] /= b;
        }
        return a;
    }
    constexpr Poly &operator+=(Poly b) {
        return (*this) = (*this) + b;
    }
    constexpr Poly &operator-=(Poly b) {
        return (*this) = (*this) - b;
    }
    constexpr Poly &operator*=(Poly b) {
        return (*this) = (*this) * b;
    }
    constexpr Poly &operator*=(Value b) {
        return (*this) = (*this) * b;
    }
    constexpr Poly &operator/=(Value b) {
        return (*this) = (*this) / b;
    }
    constexpr Poly deriv() const {
        if (this->empty()) {
            return Poly();
        }
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = (i + 1) * (*this)[i + 1];
        }
        return res;
    }
    constexpr Poly integr() const {
        Poly res(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = (*this)[i] / (i + 1);
        }
        return res;
    }
    constexpr Poly inv(int m) const {
        Poly x{(*this)[0].inv()};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }
    constexpr Poly log(int m) const {
        return (deriv() * inv(m)).integr().trunc(m);
    }
    constexpr Poly exp(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }
    constexpr Poly pow(int k, int m) const {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return Poly(m);
        }
        Value v = (*this)[i];
        auto f = shift(-i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    }
    constexpr Poly sqrt(int m) const {
        Poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, P>;
        }
        return x.trunc(m);
    }
    constexpr Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }
    constexpr std::vector<Value> eval(std::vector<Value> x) const {
        if (this->size() == 0) {
            return std::vector<Value>(x.size(), 0);
        }
        const int n = std::max(x.size(), this->size());
        std::vector<Poly> q(4 * n);
        std::vector<Value> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).trunc(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).trunc(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};
 
template<int P = 998244353>
Poly<P> berlekampMassey(const Poly<P> &s) {
    Poly<P> c;
    Poly<P> oldC;
    int f = -1;
    for (int i = 0; i < s.size(); i++) {
        auto delta = s[i];
        for (int j = 1; j <= c.size(); j++) {
            delta -= c[j - 1] * s[i - j];
        }
        if (delta == 0) {
            continue;
        }
        if (f == -1) {
            c.resize(i + 1);
            f = i;
        } else {
            auto d = oldC;
            d *= -1;
            d.insert(d.begin(), 1);
            MInt<P> df1 = 0;
            for (int j = 1; j <= d.size(); j++) {
                df1 += d[j - 1] * s[f + 1 - j];
            }
            assert(df1 != 0);
            auto coef = delta / df1;
            d *= coef;
            Poly<P> zeros(i - f - 1);
            zeros.insert(zeros.end(), d.begin(), d.end());
            d = zeros;
            auto temp = c;
            c += d;
            if (i - temp.size() > f - oldC.size()) {
                oldC = temp;
                f = i;
            }
        }
    }
    c *= -1;
    c.insert(c.begin(), 1);
    return c;
}
 
 
template<int P = 998244353>
MInt<P> linearRecurrence(Poly<P> p, Poly<P> q, i64 n) {
    int m = q.size() - 1;
    while (n > 0) {
        auto newq = q;
        for (int i = 1; i <= m; i += 2) {
            newq[i] *= -1;
        }
        auto newp = p * newq;
        newq = q * newq;
        for (int i = 0; i < m; i++) {
            p[i] = newp[i * 2 + n % 2];
        }
        for (int i = 0; i <= m; i++) {
            q[i] = newq[i * 2];
        }
        n /= 2;
    }
    return p[0] / q[0];
}
 
struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
     
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

using poly = Poly<P>;

// ===== MMT helpers & Dynamic-mod Polynomial (Mpoly) =====
// 依赖：你已提供的 MInt/Poly/dft/idft 模板（上文）。
// 注意：本实现不会再次定义它们，只是复用。

// 三个 NTT 友好模与原根=3（已知）
static constexpr int P1 = 469762049;   // 2^26 * 7 + 1
static constexpr int P2 = 998244353;   // 2^23 * 119 + 1
static constexpr int P3 = 1004535809;  // 2^21 * 479 + 1

using Z1 = MInt<P1>;
using Z2 = MInt<P2>;
using Z3 = MInt<P3>;

// 安全模乘（64位即可；若你未来要上更大模，可以换成 __int128）
static inline int addmod_i32(int a, int b, int MOD) {
    int s = a + b;
    if (s >= MOD) s -= MOD;
    return s;
}
static inline int submod_i32(int a, int b, int MOD) {
    int s = a - b;
    if (s < 0) s += MOD;
    return s;
}
static inline int mulmod_i32(int a, int b, int MOD) {
    return int((1LL * a * b) % MOD);
}
static inline int norm_i32(long long x, int MOD) {
    x %= MOD;
    if (x < 0) x += MOD;
    return int(x);
}

static long long exgcd_ll(long long a, long long b, long long& x, long long& y) {
    if (!b) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = exgcd_ll(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
static inline int inv_mod_any(int a, int MOD) {
    a = norm_i32(a, MOD);
    long long x, y;
    long long g = exgcd_ll(a, MOD, x, y);
    assert(g == 1 && "inverse does not exist modulo MOD");
    x %= MOD; if (x < 0) x += MOD;
    return int(x);
}
static inline int pow_mod_any(int a, long long e, int MOD) {
    long long r = 1, x = norm_i32(a, MOD);
    while (e > 0) {
        if (e & 1) r = (r * x) % MOD;
        x = (x * x) % MOD;
        e >>= 1;
    }
    return int(r);
}

// 若目标模恰好是某个 NTT 质数，直接单模 NTT 卷积（复用你给的 Poly<P>）
template<int P>
static std::vector<int> conv_single_prime(const std::vector<int>& A, const std::vector<int>& B) {
    if (A.empty() || B.empty()) return {};
    Poly<P> a(A.size()), b(B.size());
    for (int i = 0; i < (int)A.size(); ++i) a[i] = MInt<P>(A[i]);
    for (int j = 0; j < (int)B.size(); ++j) b[j] = MInt<P>(B[j]);
    auto c = a * b;
    std::vector<int> res(c.size());
    for (int i = 0; i < (int)c.size(); ++i) res[i] = int(c[i]);
    return res;
}

// MMT: 在 P1/P2/P3 下 NTT，再用 Garner/CRT 合并到目标 MOD
static std::vector<int> conv_mmt_crt(const std::vector<int>& A, const std::vector<int>& B, int MOD) {
    if (A.empty() || B.empty()) return {};
    int nA = (int)A.size(), nB = (int)B.size();
    int nC = nA + nB - 1;

    // 1) 三模卷积
    auto c1 = conv_single_prime<P1>(A, B); c1.resize(nC);
    auto c2 = conv_single_prime<P2>(A, B); c2.resize(nC);
    auto c3 = conv_single_prime<P3>(A, B); c3.resize(nC);

    // 2) 预计算 Garner 常量
    // t2 = (c2 - t1) * inv(P1 mod P2)  (mod P2)
    int inv_p1_p2 = int(Z2(P1).inv());
    // t3 = (c3 - (t1 + P1*t2 mod P3)) * inv(P1*P2 mod P3) (mod P3)
    int p12_mod_p3 = int((1LL * (P1 % P3) * (P2 % P3)) % P3);
    int inv_p12_p3 = int(Z3(p12_mod_p3).inv());

    int p1_mod_mod  = P1 % MOD;
    long long p12_mod_mod = (1LL * p1_mod_mod * (P2 % MOD)) % MOD;

    std::vector<int> res(nC);
    for (int i = 0; i < nC; ++i) {
        int t1 = c1[i]; // in [0, P1)
        int t2 = int(1LL * norm_i32(c2[i] - t1, P2) * inv_p1_p2 % P2);
        int tmp = norm_i32((t1 + 1LL * P1 * t2) % P3, P3);
        int t3 = int(1LL * norm_i32(c3[i] - tmp, P3) * inv_p12_p3 % P3);
        long long ans = t1 % MOD;
        ans += 1LL * p1_mod_mod * t2 % MOD;
        ans %= MOD;
        ans += (p12_mod_mod * t3) % MOD;
        ans %= MOD;
        res[i] = int(ans);
    }
    return res;
}

// 卷积总入口：若 MOD 是三大 NTT 模之一，走单模；否则走 MMT+CRT
static std::vector<int> convolve_dyn(const std::vector<int>& A, const std::vector<int>& B, int MOD) {
    if (A.empty() || B.empty()) return {};
    // 小规模直接朴素乘，省掉 MMT 开销
    if ((int)std::min(A.size(), B.size()) < 64) {
        std::vector<int> C(A.size() + B.size() - 1, 0);
        for (int i = 0; i < (int)A.size(); ++i) {
            long long ai = A[i] % MOD;
            for (int j = 0; j < (int)B.size(); ++j) {
                C[i + j] = int((C[i + j] + ai * (B[j] % MOD)) % MOD);
            }
        }
        return C;
    }
    if (MOD == P1) return conv_single_prime<P1>(A, B);
    if (MOD == P2) return conv_single_prime<P2>(A, B);
    if (MOD == P3) return conv_single_prime<P3>(A, B);
    return conv_mmt_crt(A, B, MOD);
}

// --------- Tonelli-Shanks (mod 必须为奇素数) ----------
static long long legendre_symbol(long long a, long long p) {
    return pow_mod_any((int)a, (p - 1) / 2, (int)p);
}
static int mod_sqrt_prime(int a, int p) {
    a = norm_i32(a, p);
    if (a == 0) return 0;
    if (p == 2) return a;
    // 检查二次剩余
    if (legendre_symbol(a, p) != 1) {
        // 无解：返回 -1，外层需处理
        return -1;
    }
    if (p % 4 == 3) {
        return pow_mod_any(a, (p + 1) / 4, p);
    }
    // Tonelli-Shanks
    int q = p - 1, s = 0;
    while ((q & 1) == 0) q >>= 1, ++s;
    int z = 2;
    while (legendre_symbol(z, p) != p - 1) z++;
    long long c = pow_mod_any(z, q, p);
    long long x = pow_mod_any(a, (q + 1) / 2, p);
    long long t = pow_mod_any(a, q, p);
    int m = s;
    while (t != 1) {
        int i = 1;
        long long tt = (t * t) % p;
        while (tt != 1) {
            tt = (tt * tt) % p;
            ++i;
            if (i == m) break;
        }
        long long b = c;
        for (int e = 0; e < m - i - 1; ++e) b = (b * b) % p;
        x = (x * b) % p;
        c = (b * b) % p;
        t = (t * c) % p;
        m = i;
    }
    return int(x);
}

// ===================== 动态模多项式 =====================
struct Mpoly : public std::vector<int> {
    using VI = std::vector<int>;

    static int Mod;           // 目标模数（动态）
    static bool AssumePrime;  // 是否假定 Mod 为素数（影响逆元/积分/TS 等）

    static void set_mod(int mod, bool assume_prime = true) {
        Mod = mod; AssumePrime = assume_prime;
    }
    static int get_mod() { return Mod; }

    Mpoly() : std::vector<int>() {}
    explicit Mpoly(int n) : std::vector<int>(n, 0) {}
    explicit Mpoly(const VI& a) : std::vector<int>(a) {
        for (auto& x : *this) x = norm_i32(x, Mod);
    }
    Mpoly(std::initializer_list<int> a) : std::vector<int>(a) {
        for (auto& x : *this) x = norm_i32(x, Mod);
    }

    // 工具
    Mpoly trunc(int k) const {
        Mpoly f = *this;
        if ((int)f.size() > k) f.resize(k);
        return f;
    }
    Mpoly shift(int k) const {
        if (k >= 0) {
            Mpoly b(k + size());
            for (int i = 0; i < (int)size(); ++i) b[i + k] = (*this)[i];
            return b;
        } else {
            int kk = -k;
            if ((int)size() <= kk) return Mpoly();
            return Mpoly(VI(begin() + kk, end()));
        }
    }
    static void shrink(Mpoly& f) {
        while (!f.empty() && f.back() == 0) f.pop_back();
    }

    // 基本四则
    friend Mpoly operator+(const Mpoly& a, const Mpoly& b) {
        Mpoly c(std::max(a.size(), b.size()));
        for (int i = 0; i < (int)a.size(); ++i) c[i] = addmod_i32(c[i], a[i], Mod);
        for (int i = 0; i < (int)b.size(); ++i) c[i] = addmod_i32(c[i], b[i], Mod);
        shrink(c); return c;
    }
    friend Mpoly operator-(const Mpoly& a, const Mpoly& b) {
        Mpoly c(std::max(a.size(), b.size()));
        for (int i = 0; i < (int)a.size(); ++i) c[i] = addmod_i32(c[i], a[i], Mod);
        for (int i = 0; i < (int)b.size(); ++i) c[i] = submod_i32(c[i], b[i], Mod);
        shrink(c); return c;
    }
    friend Mpoly operator-(const Mpoly& a) {
        Mpoly c(a.size());
        for (int i = 0; i < (int)a.size(); ++i) c[i] = a[i] ? (Mod - a[i]) : 0;
        return c;
    }
    friend Mpoly operator*(const Mpoly& a, const Mpoly& b) {
        if (a.empty() || b.empty()) return Mpoly();
        auto C = convolve_dyn((const VI&)a, (const VI&)b, Mod);
        return Mpoly(C);
    }
    friend Mpoly operator*(const Mpoly& a, int b) {
        if (a.empty()) return Mpoly();
        int bb = norm_i32(b, Mod);
        Mpoly c(a.size());
        for (int i = 0; i < (int)a.size(); ++i) c[i] = mulmod_i32(a[i], bb, Mod);
        shrink(c); return c;
    }
    friend Mpoly operator*(int a, const Mpoly& b) { return b * a; }

    friend Mpoly operator/(const Mpoly& a, int b) {
        int invb = AssumePrime ? pow_mod_any(b, Mod - 2, Mod) : inv_mod_any(b, Mod);
        return a * invb;
    }

    Mpoly& operator+=(const Mpoly& b) { return *this = *this + b; }
    Mpoly& operator-=(const Mpoly& b) { return *this = *this - b; }
    Mpoly& operator*=(const Mpoly& b) { return *this = *this * b; }
    Mpoly& operator*=(int b) { return *this = *this * b; }
    Mpoly& operator/=(int b) { return *this = *this / b; }

    // 微分/积分
    Mpoly deriv() const {
        if (empty()) return Mpoly();
        Mpoly r(std::max(0, (int)size() - 1));
        for (int i = 1; i < (int)size(); ++i) r[i - 1] = mulmod_i32((*this)[i], i, Mod);
        shrink(r); return r;
    }
    Mpoly integr() const {
        Mpoly r(size() + 1);
        r[0] = 0;
        for (int i = 0; i < (int)size(); ++i) {
            int den = i + 1;
            int invd = AssumePrime ? pow_mod_any(den, Mod - 2, Mod) : inv_mod_any(den, Mod);
            r[i + 1] = mulmod_i32((*this)[i], invd, Mod);
        }
        shrink(r); return r;
    }

    // 1/f 取前 m 项（Newton）
    Mpoly inv(int m) const {
        assert(!empty() && (*this)[0] != 0);
        int inv_a0 = AssumePrime ? pow_mod_any((*this)[0], Mod - 2, Mod) : inv_mod_any((*this)[0], Mod);
        Mpoly x(1); x[0] = inv_a0;
        int k = 1;
        while (k < m) {
            k <<= 1;
            Mpoly f = this->trunc(k);
            Mpoly t = x * x * f;   // x * (2 - f*x) = 2x - x*x*f
            t = (x * 2) - t;
            x = t.trunc(k);
        }
        return x.trunc(m);
    }

    // ln(f)，默认 f[0] == 1
    Mpoly log(int m) const {
        assert(!empty() && (*this)[0] == 1);
        return (this->deriv() * this->inv(m)).integr().trunc(m);
    }

    // exp(f)，默认 f[0] == 0
    Mpoly exp(int m) const {
        assert(empty() || (*this)[0] == 0);
        Mpoly x(1); x[0] = 1;
        int k = 1;
        while (k < m) {
            k <<= 1;
            // x = x * (1 - ln(x) + f)  (mod x^k)
            Mpoly t = x.log(k);
            t = (-t) + this->trunc(k);
            t[0] = addmod_i32(t[0], 1, Mod);
            x = (x * t).trunc(k);
        }
        return x.trunc(m);
    }

    // f^k 取前 m 项
    Mpoly pow(long long k, int m) const {
        if (m == 0) return Mpoly();
        if (empty()) return Mpoly(m); // 全 0
        int i = 0;
        while (i < (int)size() && (*this)[i] == 0) ++i;
        if (i == (int)size()) return Mpoly(m); // 0 多项式
        long long shift = 1LL * i * k;
        if (shift >= m) return Mpoly(m);
        int a0 = (*this)[i];
        int inv_a0 = AssumePrime ? pow_mod_any(a0, Mod - 2, Mod) : inv_mod_any(a0, Mod);
        // g = (f >> i) / a0
        Mpoly g = this->shift(-i) * inv_a0;
        // (ln g)*k 再 exp
        Mpoly h = (g.log(m - (int)shift) * int(norm_i32(k % Mod, Mod))).exp(m - (int)shift);
        // 乘回 a0^k 并左移
        int a0k = pow_mod_any(a0, k, Mod);
        h *= a0k;
        h = h.shift((int)shift);
        return h.trunc(m);
    }

    // sqrt(f) 取前 m 项：需已知 a0 的平方根存在
    Mpoly sqrt(int m) const {
        assert(!empty());
        int a0 = (*this)[0];
        int r0;
        if (AssumePrime) {
            r0 = mod_sqrt_prime(a0, Mod);
            assert(r0 != -1 && "constant term is not a quadratic residue");
        } else {
            // 不假定质数：你需要自行提供 a0 的根（或禁用 sqrt）
            // 这里给个保守断言；若要支持，可替换为其他算法。
            assert(false && "sqrt requires prime modulus or user-supplied root");
            r0 = 0;
        }
        Mpoly x(1); x[0] = r0;
        int inv2 = AssumePrime ? pow_mod_any(2, Mod - 2, Mod) : inv_mod_any(2, Mod);
        int k = 1;
        while (k < m) {
            k <<= 1;
            // x_{new} = (x + f / x) / 2
            // 其中 f/x = f * inv(x)
            Mpoly fx = (this->trunc(k) * x.inv(k)).trunc(k);
            Mpoly t = x + fx;
            for (int i = 0; i < (int)t.size(); ++i) t[i] = mulmod_i32(t[i], inv2, Mod);
            x = t.trunc(k);
        }
        return x.trunc(m);
    }

    // 反转卷积（T-卷积）：与你 Poly 的 mulT 等价
    Mpoly mulT(Mpoly b) const {
        if (b.empty()) return Mpoly();
        int n = (int)b.size();
        std::reverse(b.begin(), b.end());
        Mpoly c = (*this) * b;
        return c.shift(-(n - 1));
    }

    vector<int> eval(std::vector<int> x) const {
        if (this->size() == 0) {
            return std::vector<int>(x.size(), 0);
        }
        const int n = std::max(x.size(), this->size());
        std::vector<Mpoly> q(4 * n);
        std::vector<int> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Mpoly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Mpoly &)> work = [&](int p, int l, int r, const Mpoly &num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).trunc(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).trunc(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

// 静态成员定义
int  Mpoly::Mod = 998244353;
bool Mpoly::AssumePrime = true;



void solve()
{
    int n, p;
    cin >> n >> p;
    Mpoly::set_mod(p);
    int sq = sqrt(n);
    cerr << Mpoly::Mod << endl;
    auto build = [&](auto&&self, int l, int r, int p)->Mpoly
    {
        if(l == r){
            return Mpoly{l, 1};
        }
        int mid = l + r >> 1;
        return self(self, l, mid , p * 2) * self(self, mid + 1, r, p * 2 + 1);
    };
    auto f = build(build, 0, sq - 1, 1);
    vector<int>x(sq);
    for(int i = 0;i < sq;i++){
        x[i] = i * sq + 1;
       
    }
    auto v = f.eval(x);
    Z ans = 1;
    for(int i = 0;i < sq;i++){
        ans *= v[i];
    }
    for(int i = sq * sq + 1;i <= n;i++){
        ans *= i;
    }
    for(int i = sq * sq;i > n;i--){
        ans /= i;
    }
    cout << ans << endl;
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