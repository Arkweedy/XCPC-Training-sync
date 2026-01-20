#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//polys.cpp Create time : 2026.01.13 22:21
constexpr int P = 998244353;
constexpr int G = 3;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int power(int a, int p, int M)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % M;
        a = 1ll * a * a % M;
        p >>= 1;
    }
    return res;
}

int inv(int a)
{
    return power(a, P - 2);
}

int bsgs(int a, int b, int p)
{
    a %= p;
    b %= p;
    if(p == 1) return 0;
    if(b == 1) return 0;

    int sq = ceil(sqrt(p));

    unordered_map<int,int>mp;
    int x = 1;
    for(int i = 0;i <= sq;i++){
        mp[1ll * x * b % p] = i;
        x = 1ll * x * a % p;
    }

    int asq = power(a, sq, p);
    int y = asq;
    for(int i = 1;i <= sq;i++){
        if(mp.find(y) != mp.end()){
            return i * sq - mp[y];
        }
        y = 1ll * y * asq % p;
    }
    return -1;
}

int Fsqrt(int x)
{
    int p = bsgs(G, x, P);
    return power(G, p / 2);
}

void dft(vector<int>& f)
{
    int n = f.size();
    int j = 0;
    for(int i = 1;i < n;i++){
        int k = n >> 1;
        for(;k & j;k >>= 1){
            j ^= k;
        }
        j ^= k;
        if(j < i){
            swap(f[i], f[j]);
        }
    }


    int wn = power(G, (P - 1) / n);
    for(int len = 2;len <= n;len <<= 1){
        int wlen = power(wn, n / len);
        vector<int>w(len / 2);
        w[0] = 1;
        for(int i = 1;i < len / 2;i++){
            w[i] = 1ll * w[i - 1] * wlen % P;
        }
        for(int i = 0;i < n;i += len){
            for(int j = 0;j < len / 2;j++){
                int u = f[i + j], v = 1ll * f[i + j + len / 2] * w[j] % P;
                f[i + j] = (u + v) % P;
                f[i + j + len / 2] = (u - v + P) % P;
            }
        }
    }
    return;
}

void idft(vector<int>& f)
{
    int n = f.size();
    int invn = inv(n);
    reverse(f.begin() + 1, f.end());
    dft(f);
    for(int i = 0;i < n;i++){
        f[i] = 1ll * f[i] * invn % P;
    }
    return;
}

class poly : public vector<int>
{
public:
    poly() : vector<int>(){}

    template<class F>
    explicit constexpr poly(int n, F f) : vector<int>(n)
    {
        for(int i = 0;i < n;i++){
            (*this)[i] = f(i);
        }
    }
    template<class InputIt, class = std::_RequireInputIter<InputIt>>
    explicit constexpr poly(InputIt first, InputIt last) : std::vector<int>(first, last) {}
    
    explicit constexpr poly(int n, int val) : vector<int>(n, val){}
    explicit constexpr poly(int n) : vector<int>(n){}
    explicit constexpr poly(const std::vector<int> &a) : std::vector<int>(a) {}
    constexpr poly(const std::initializer_list<int> &a) : vector<int>(a){}

    constexpr friend poly operator+(const poly &a, const poly &b) {
        poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] = a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] = (res[i] + b[i]) % P;
        }
        return res;
    }
    constexpr friend poly operator-(const poly &a, const poly &b) {
        poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] = a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] = (res[i] - b[i] + P) % P;
        }
        return res;
    }
    constexpr friend poly operator-(const poly &a) {
        std::vector<int> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = P - a[i];
            if(res[i] == P)res[i] = 0;
        }
        return poly(res);
    }
    constexpr friend poly operator*(int a, poly b) {
        a = (a % P + P) % P;
        for (int i = 0; i < int(b.size()); i++) {
            b[i] = 1ll * b[i] * a % P;
        }
        return b;
    }
    constexpr friend poly operator*(poly a, int b) {
        b = (b % P + P) % P;
        for (int i = 0; i < int(a.size()); i++) {
            a[i] = 1ll * a[i] * b % P;
        }
        return a;
    }
    constexpr friend poly operator/(poly a, int b) {
        int invb = power(b, P - 2);
        for (int i = 0; i < int(a.size()); i++) {
            a[i] = 1ll * a[i] * invb % P;
        }
        return a;
    }

    constexpr friend poly operator/(const poly &a, const poly &b) {
        if(a.size() < b.size())return poly();
        int k = a.size() - b.size() + 1;
        return (a.rev().trunc(k) * b.rev().inv(k).trunc(k)).trunc(k).rev();
    }
    constexpr friend poly operator%(const poly &a, const poly &b) {
        return (a - a / b * b).trunc(min(a.size(), b.size() - 1));
    }

    constexpr poly &operator+=(poly b) {
        return (*this) = (*this) + b;
    }
    constexpr poly &operator-=(poly b) {
        return (*this) = (*this) - b;
    }
    constexpr poly &operator*=(poly b) {
        return (*this) = (*this) * b;
    }
    constexpr poly &operator*=(int b) {
        return (*this) = (*this) * b;
    }
    constexpr poly &operator/=(int b) {
        return (*this) = (*this) / b;
    }

    constexpr friend poly operator*(poly a, poly b) {
        if (a.size() == 0 || b.size() == 0) {
            return poly();
        }
        if (a.size() < b.size()) {
            std::swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] = (c[i + j] + 1ll * a[i] * b[j]) % P;
                }
            }
            return c;
        }
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (int i = 0; i < n; ++i) {
            a[i] = 1ll * a[i] * b[i] % P; 
        }
        idft(a);
        a.resize(tot);
        return a;
    }

    constexpr poly shift(int k) const {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return poly();
        } else {
            return poly(this->begin() + (-k), this->end());
        }
    }

    constexpr poly trunc(int k) const {
        poly f = *this;
        f.resize(k);
        return f;
    }

    constexpr poly deriv() const {
        if (this->empty()) {
            return poly();
        }
        poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = 1ll * (i + 1) * (*this)[i + 1] % P;
        }
        return res;
    }

    constexpr poly integr() const {
        poly res(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = 1ll * (*this)[i] * power(i + 1, P - 2) % P;
        }
        return res;
    }

    constexpr poly rev() const{
        poly res = *this;
        while(res.back() == 0)res.pop_back();
        reverse(res.begin(),res.end());
        return res;
    }

    constexpr poly inv(int m) const {
        poly x{power((*this)[0], P - 2)};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }

    constexpr poly log(int m) const {
        return (deriv() * inv(m)).integr().trunc(m);
    }

    constexpr poly exp(int m) const {
        poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }

    constexpr poly exp2(int m) const {
        poly f(m), h = deriv();
        h.resize(m);
        f[0] = 1;
        // fn = 1/n(\sum h_k f_{n - 1 - k})
        auto cdq = [&](auto&&self, int l ,int r)->void
        {
            if(l == r){
                if(l == 0)return;
                f[l] = 1ll * f[l] * power(l, P - 2) % P;
                return;
            }
            int m = l + r >> 1;
            self(self, l, m);
            poly a(m - l + 1),b(r - l);
            for(int i = 0;i <= m - l;i++){
                a[i] = f[i + l];
            }
            for(int i = 0;i < r - l;i++){
                b[i] = h[i];
            }
            auto c = a * b;
            for(int i = 0;i < r - m;i++){
                f[m + i + 1] = (f[m + i + 1] + c[i + m - l]) % P;
            }
            self(self, m + 1, r);
            return;
        };
        cdq(cdq, 0, m - 1);
        return f;
    }

    constexpr poly pow(int k, int m) const {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return poly(m);
        }
        int v = (*this)[i];
        auto f = shift(-i) * power(v, P - 2);
        return ((f.log(m - i * k) * k).exp2(m - i * k).shift(i * k)) * power(v, k);
    }

    constexpr poly pow(int k, int kmodphiP,int big, int m) const {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return poly(m);
        }
        if(big && i > 0)return poly(m);//x^{big number} f(x)^{k}
        int v = (*this)[i];
        auto f = shift(-i) * power(v, P - 2);
        return ((f.log(m - i * k) * k).exp2(m - i * k).shift(i * k)) * power(v, kmodphiP);
    }

    constexpr poly sqrt(int m) const {
        poly x{Fsqrt((*this)[0])};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * power(2, P - 2);
        }
        return x.trunc(m);
    }

    constexpr vector<int> eval2(vector<int> x)const 
    {
        if(this->size() == 0){
            return vector<int>(x.size(), 0);
        }
        if(x.size() == 0){
            return vector<int>(0);
        }
        int n = x.size();
        for(int i = 0;i < n;i++){ //norm P - x[i]
            if(x[i] <= 0)x[i] += P;
            if(x[i] > P)x[i] -= P;
        }
        vector<poly>m(n * 4);//segtree
        auto build = [&](auto&&self, int l, int r, int p)->void
        {
            if(l == r){
                m[p] = poly{P - x[l], 1};
                return;
            }
            int mid = l + r >> 1;
            self(self, l, mid , p * 2);
            self(self, mid + 1, r, p * 2 + 1);
            m[p] = m[p * 2] * m[p * 2 + 1];
            return;
        };
        build(build, 0, n - 1, 1);
        vector<int>ans(n);
        auto work = [&](auto&&self,const poly &f, int l, int r, int p)->void
        {
            if(l == r){
                ans[l] = f[0];
                return;
            }
            int mid = l + r >> 1;
            self(self, f % m[p * 2], l, mid, p * 2);
            self(self, f % m[p * 2 + 1], mid + 1, r, p * 2 + 1);
            return;
        };
        work(work, *this, 0, n - 1, 1);
        return ans;
    }

    constexpr poly mulT(poly b) const {
        if (b.size() == 0) {
            return poly();
        }
        int n = b.size();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }

    constexpr vector<int> eval(vector<int> x)const 
    {
        if(this->size() == 0){
            return vector<int>(x.size(), 0);
        }
        if(x.size() == 0){
            return vector<int>(0);
        }
        int n = max(x.size(), this->size()); // !!!
        x.resize(n);
        for(int i = 0;i < n;i++){ //norm P - x[i]
            if(x[i] <= 0)x[i] += P;
            if(x[i] > P)x[i] -= P;
        }
        vector<poly>m(n * 4);//segtree build Q(x)
        auto build = [&](auto&&self, int l, int r, int p)->void
        {
            if(l == r){
                m[p] = poly{1, P - x[l]};
                return;
            }
            int mid = l + r >> 1;
            self(self, l, mid , p * 2);
            self(self, mid + 1, r, p * 2 + 1);
            m[p] = m[p * 2] * m[p * 2 + 1];
            return;
        };
        build(build, 0, n - 1, 1);
        vector<int>ans(n);
        auto work = [&](auto&&self,const poly &f, int l, int r, int p)->void
        {
            if(l == r){
                ans[l] = f[0];
                return;
            }
            int mid = l + r >> 1;
            self(self, f.mulT(m[p * 2 + 1]).trunc(mid - l + 1), l, mid, p * 2);
            self(self, f.mulT(m[p * 2]).trunc(r - mid), mid + 1, r, p * 2 + 1);
            return;
        };
        work(work, mulT(m[1].inv(n)).trunc(n), 0, n - 1, 1);
        return ans;
    }
};

constexpr poly lagrange(vector<int>x, vector<int>y)
{
    assert(x.size() == y.size());
    if(x.size() == 0)return poly();
    int n = x.size();
    for(int i = 0;i < n;i++){ //norm P - x[i]
        if(x[i] <= 0)x[i] += P;
        if(x[i] > P)x[i] -= P;
    }
    for(int i = 0;i < n;i++){ //norm P - x[i]
        if(y[i] <= 0)y[i] += P;
        if(y[i] > P)y[i] -= P;
    }
    vector<poly>m(n * 4);//segtree build Q(x)
    auto build = [&](auto&&self, int l, int r, int p)->void
    {
        if(l == r){
            m[p] = poly{P - x[l], 1};
            return;
        }
        int mid = l + r >> 1;
        self(self, l, mid , p * 2);
        self(self, mid + 1, r, p * 2 + 1);
        m[p] = m[p * 2] * m[p * 2 + 1];
        return;
    };
    build(build, 0, n - 1, 1);
    auto dM = m[1].deriv();
    auto v = dM.eval(x);
    for(int i = 0;i < n;i++){
        v[i] = 1ll * power(v[i], P - 2) * y[i] % P;
    }

    auto work = [&](auto&&self, int l, int r, int p)->poly
    {
        if(l == r){
            return poly{v[l]};
        }
        int mid = l + r >> 1;
        return m[p * 2] * self(self, mid + 1, r, p * 2 + 1) + m[p * 2 + 1] * self(self, l, mid, p * 2);
    };
    return work(work, 0, n - 1, 1);
}

int kitamasa(vector<int> a, vector<int> c, i64 n) //f_0~f_{k - 1} -> f_n
{
    assert(c.size() == a.size() + 1);
    int k = a.size();
    poly chi(k + 1);
    for(int i = 0;i < k;i++){
        chi[i] = P - c[k - i];
        if(chi[i] >= P)chi[i] -= P;
    }
    chi[k] = 1;
    
    poly res{1};
    poly x{0, 1};
    while(n){
        if(n & 1)res = res * x % chi;
        x = x * x % chi;
        n >>= 1;
    }

    int ans = 0;
    for(int i = 0;i < k;i++){
        ans = (ans + 1ll * res[i] * a[i]) % P;
    }
    ans = (ans % P + P) % P;
    return ans;
}

int bostanMori(poly& p, poly& q, i64 n)
{
    int m = q.size() - 1;
    
    while (n > 0) {
        poly nq = q;
        for (int i = 1; i <= m; i += 2) {
            nq[i] = -q[i];
            if(nq[i] < 0)nq[i] += P;
        }
        auto np = p * nq;
        nq = q * nq;
        for (int i = 0; i < m; i++) {
            p[i] = np[i * 2 + n % 2];
        }
        for (int i = 0; i <= m; i++) {
            q[i] = nq[i * 2];
        }
        n /= 2;
    }
    return 1ll * p[0] * inv(q[0]) % P;
}

int linearRecurrence(poly a, poly c, i64 n) //a_0 ... a_{k - 1} , c_1 ... c_k
{
    assert(a.size() + 1 == c.size());
    assert(c[0] == 0);
    int k = a.size();
    poly p = a - (a * c).trunc(k), q = poly{1} - c;
    return bostanMori(p, q, n);
}

// 需要：全局模数 P；你的 poly 支持：
// - poly(int n) / resize / operator[]
// - operator* (NTT/暴力自动选择)
// - inv(int m), trunc(int m), shift(int k)
// 你给的 shift/trunc 语义是 OK 的（shift(-t) = 丢前 t 项）。

static inline int ceil_pow2_int(int n) {
    int p = 1;
    while (p < n) p <<= 1;
    return p;
}
static inline int mod_neg(int x) { return x ? (P - x) : 0; }

// 定长反转：保证长度不变
static inline poly revN(poly a, int n) {
    a = a.trunc(n);
    std::reverse(a.begin(), a.end());
    return a;
}

// 连续存二维：按 x-major, y contiguous：a[x*ky + y]
struct biMat {
    int nx; // x 长度 = n+1
    int ky; // y 长度 = k+1
    poly a; // size = nx*ky
    biMat() : nx(0), ky(0), a() {}
    biMat(int _nx, int _ky) : nx(_nx), ky(_ky), a(_nx * _ky) {}
    inline int& at(int x, int y) { return a[x * ky + y]; }
    inline const int& at(int x, int y) const { return a[x * ky + y]; }
};

// pack: 把 biMat 以 idx = x*stride + y 打包成 1D poly（stride >= ky）
static inline poly pack_2d(const biMat& M, int stride) {
    poly p(M.nx * stride);
    for (int x = 0; x < M.nx; ++x) {
        int dst = x * stride;
        int src = x * M.ky;
        for (int y = 0; y < M.ky; ++y) p[dst + y] = M.a[src + y];
    }
    return p;
}

// pack Q(-x,y)：不显式构造 R，打包时对奇数 x 行取负
static inline poly pack_Q_negx(const biMat& Q, int stride) {
    poly p(Q.nx * stride);
    for (int x = 0; x < Q.nx; ++x) {
        int dst = x * stride;
        int src = x * Q.ky;
        if (x & 1) {
            for (int y = 0; y < Q.ky; ++y) p[dst + y] = mod_neg(Q.a[src + y]);
        } else {
            for (int y = 0; y < Q.ky; ++y) p[dst + y] = Q.a[src + y];
        }
    }
    return p;
}

// 构造 revR（editorial 的 revR[i] = R[n-i].rev()），但直接打包到 stride=2k+1
static inline poly pack_revR_from_Q(const biMat& Q, int n, int k, int stride_2k1) {
    // revR 视作 (n+1) x (2k+1)，只填 y=0..k，y>k 为 0
    poly p((n + 1) * stride_2k1);
    for (int x = 0; x <= n; ++x) {
        int src_x = n - x;          // 取 R[n-x]
        bool neg  = (src_x & 1);    // R = Q(-x) => R[src_x] = (-1)^{src_x} Q[src_x]
        int dst = x * stride_2k1;
        int src = src_x * Q.ky;
        // rev(): y -> k - y
        for (int y = 0; y <= k; ++y) {
            int v = Q.a[src + (k - y)];
            if (neg) v = mod_neg(v);
            p[dst + y] = v;
        }
    }
    return p;
}

// inner(g, Q, n, k) 的打包优化版本（对齐 editorial）
// 输入：Q 形状 (n+1) x (k+1)
// 返回：P 形状 (n+1) x (k+1)
static biMat inner_KL_fast(const poly& gY, const biMat& Q, int n, int k) {
    if (n == 0) {
        // editorial: h = g * Q0.inv().rev(); P0[i] = h[i + Q0.size() - 1]
        poly q0(k + 1);
        for (int y = 0; y <= k; ++y) q0[y] = Q.at(0, y);

        poly invq0 = q0.inv(k + 1);
        std::reverse(invq0.begin(), invq0.end()); // 定长 rev，invq0 长度 k+1

        poly h = gY * invq0; // 长度约 gY.size + (k+1) -1

        biMat P(1, k + 1);
        int off = (int)q0.size() - 1; // = k
        int lim = (int)gY.size();     // editorial 用 g.size()
        lim = std::min(lim, k + 1);   // 防越界/保证 P 维度
        for (int i = 0; i < lim; ++i) {
            int idx = i + off;
            P.at(0, i) = (idx < (int)h.size()) ? h[idx] : 0;
        }
        // 其余系数自然保持 0
        return P;
    }

    // stride = 2k+1，对应 ydeg <= 2k 的部分（足够恢复后面要用的 y in [k,2k]）:contentReference[oaicite:4]{index=4}
    int stride = 2 * k + 1;

    // 1) T = multiply2d(Q, R), R = Q(-x)
    // 只需要 T 的偶数 x 行来构造 V
    poly pQ = pack_2d(Q, stride);
    poly pR = pack_Q_negx(Q, stride);
    poly pT = pQ * pR; // 1D 卷积等价于 2D 卷积（因为 stride 足够大）

    // 2) V[i] = T[2i], 维度：(n/2+1) x (2k+1)
    int nxV = n / 2 + 1;
    biMat V(nxV, stride);
    for (int i = 0; i < nxV; ++i) {
        int src_row = (2 * i) * stride;
        int dst_row = i * stride;
        for (int y = 0; y < stride; ++y) {
            int idx = src_row + y;
            V.a[dst_row + y] = (idx < (int)pT.size()) ? pT[idx] : 0;
        }
    }

    // 3) U = inner(g, V, n/2, 2k)
    biMat U = inner_KL_fast(gY, V, n / 2, 2 * k);

    // 4) 构造 S：大小 (2n+1) x (2k+1)，只在 x = 2i + n%2 处放 U[i]
    poly pS((2 * n + 1) * stride);
    int b = n % 2;
    for (int i = 0; i < nxV; ++i) {
        int x = 2 * i + b;
        int dst = x * stride;
        int src = i * stride; // U.ky == stride
        for (int y = 0; y < stride; ++y) pS[dst + y] = U.a[src + y];
    }

    // 5) revR 打包 & Pshift = multiply2d(S, revR)
    poly pRevR = pack_revR_from_Q(Q, n, k, stride);
    poly pPshift = pS * pRevR; // ★关键修正：这里必须是普通乘法，不是 mulT

    // 6) P[i][j] = Pshift[i+n][j+k]
    biMat P(n + 1, k + 1);
    for (int i = 0; i <= n; ++i) {
        int base = (i + n) * stride + k;
        int dst  = i * (k + 1);
        for (int j = 0; j <= k; ++j) {
            int idx = base + j;
            P.a[dst + j] = (idx < (int)pPshift.size()) ? pPshift[idx] : 0;
        }
    }
    return P;
}

// 对外：返回 outer(inner(x)) mod x^m，要求 inner[0]==0
poly comp(poly outer, poly inner, int m) {
    if (m <= 0) return poly();
    if (m == 1) return poly{ outer.size() ? outer[0] : 0 };

    int N = ceil_pow2_int(m);

    outer = outer.trunc(N);
    inner = inner.trunc(N);
    outer.resize(N);
    inner.resize(N);

    // 要求 inner[0] == 0（否则需要先平移处理）
    // assert(inner[0] == 0);

    int n = N - 1, k = 1;

    // Q(x,y) = 1 - y * inner(x)  —— 注意这里用的是 inner
    biMat Q(n + 1, k + 1);
    Q.at(0, 0) = 1;
    for (int i = 0; i <= n; ++i) Q.at(i, 1) = mod_neg(inner[i]);

    // inner() 的参数 gY 在推导里视为“y 多项式”，这里传 outer（对齐 editorial）:contentReference[oaicite:5]{index=5}
    biMat P = inner_KL_fast(outer, Q, n, k);

    poly h(N);
    for (int i = 0; i <= n; ++i) h[i] = P.at(i, 0);
    std::reverse(h.begin(), h.end());
    return h.trunc(m);
}






void solve()
{
    int n, m;
    cin >> n >> m;
    poly f(n + 1), g(m + 1);
    for(int i = 0;i <= n;i++){
        cin >> f[i];
    }
    for(int i = 0;i <= m;i++){
        cin >> g[i];
    }
    auto h = comp(f, g, n + 1);
    for(int i = 0;i <= n;i++){
        cout << h[i] << " ";
    }
    cout << endl;
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