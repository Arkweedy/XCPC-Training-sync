#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.16 10:44:46
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

struct Comb {
    int n;
    std::vector<int> _fac;
    std::vector<int> _invfac;
    std::vector<int> _inv;
     
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
            _fac[i] = 1ll * _fac[i - 1] * i % P;
        }
        _invfac[m] = power(_fac[m], P - 2);
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % P;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % P;
        }
        n = m;
    }
     
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % P * invfac(n - m) % P;
    }
} comb;


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

constexpr int Q = 23; //998244353 = K 2^Q + 1
constexpr int MAX_LEN = 22;

array<int, 1 << MAX_LEN> omega()
{
    array<int, 1 << MAX_LEN> res;
    res.fill(1);
    for (int i = 1; i <= (1 << MAX_LEN - 1); i <<= 1) {
        int wi = power(G, (P - 1) / (i * 2));
        for (int j = 1; j < i; j++) {
            res[i + j] = 1ll * res[i + j - 1] * wi % P;
        }
    }
    return res;
}

const array<int, 1 << MAX_LEN> W = omega();

void dft(vector<int>& f)
{
    int n = (int)f.size();

    // DIF: input natural order, output bit-reversed order
    for (int k = n >> 1; k; k >>= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; j++) {
                int x = f[i + j];
                int y = f[i + j + k];

                // f[i+j] = x + y
                int s = x + y;
                if (s >= P) s -= P;
                f[i + j] = s;

                // f[i+j+k] = (x - y) * W[k+j]
                int d = x - y;
                if (d < 0) d += P;
                f[i + j + k] = 1ll * d * W[k + j] % P;
            }
        }
    }
    return;
}

void idft(vector<int>& f)
{
    int n = (int)f.size();
    int invn = inv(n);

    // IDIT: take bit-reversed order (from DIF), output natural order
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k << 1) {
            for (int j = 0; j < k; j++) {
                int x = f[i + j];
                int y = 1ll * f[i + j + k] * W[k + j] % P;

                int s = x + y;
                if (s >= P) s -= P;

                int d = x - y;
                if (d < 0) d += P;

                f[i + j] = s;
                f[i + j + k] = d;
            }
        }
    }

    // scale by 1/n
    for (int i = 0; i < n; i++) {
        f[i] = 1ll * f[i] * invn % P;
    }

    // reverse except f[0]  (invNTT trick with +roots)
    reverse(f.begin() + 1, f.end());
    return;
}

class poly : public vector<int>
{
public:
    poly() : vector<int>(){}

    template<class F>
    explicit poly(int n, F f) : vector<int>(n)
    {
        for(int i = 0;i < n;i++){
            (*this)[i] = f(i);
        }
    }
    template<class InputIt, class = std::_RequireInputIter<InputIt>>
    explicit poly(InputIt first, InputIt last) : vector<int>(first, last) {}
    
    explicit poly(int n, int val) : vector<int>(n, val){}
    explicit poly(int n) : vector<int>(n){}
    explicit poly(const vector<int> &a) : vector<int>(a) {}
    poly(const std::initializer_list<int> &a) : vector<int>(a){}

    friend poly operator+(const poly &a, const poly &b) {
        poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] = a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] = res[i] + b[i];
            if(res[i] >= P)res[i] -= P;
        }
        return res;
    }
    friend poly operator-(const poly &a, const poly &b) {
        poly res(std::max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] = a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] = res[i] - b[i];
            if(res[i] < 0)res[i] += P;
        }
        return res;
    }
    friend poly operator-(const poly &a) {
        std::vector<int> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = a[i] ? P - a[i] : 0;
        }
        return poly(res);
    }
    friend poly operator*(int a, poly b) {
        a = (a % P + P) % P;
        for (int i = 0; i < int(b.size()); i++) {
            b[i] = 1ll * b[i] * a % P;
        }
        return b;
    }
    friend poly operator*(poly a, int b) {
        b = (b % P + P) % P;
        for (int i = 0; i < int(a.size()); i++) {
            a[i] = 1ll * a[i] * b % P;
        }
        return a;
    }
    friend poly operator/(poly a, int b) {
        b = (b % P + P) % P;
        int invb = power(b, P - 2);
        for (int i = 0; i < int(a.size()); i++) {
            a[i] = 1ll * a[i] * invb % P;
        }
        return a;
    }

    friend poly operator/(const poly &a, const poly &b) {
        if(a.size() < b.size())return poly();
        int k = a.size() - b.size() + 1;
        return (a.rev().trunc(k) * b.rev().inv(k).trunc(k)).trunc(k).rev();
    }
    friend poly operator%(const poly &a, const poly &b) {
        return (a - a / b * b).trunc(min(a.size(), b.size() - 1));
    }

    poly &operator+=(poly b) {
        return (*this) = (*this) + b;
    }
    poly &operator-=(poly b) {
        return (*this) = (*this) - b;
    }
    poly &operator*=(poly b) {
        return (*this) = (*this) * b;
    }
    poly &operator*=(int b) {
        return (*this) = (*this) * b;
    }
    poly &operator/=(int b) {
        return (*this) = (*this) / b;
    }

    friend poly operator*(poly a, poly b) {
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

    poly shift(int k) const {
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

    poly trunc(int k) const {
        poly f = *this;
        f.resize(k);
        return f;
    }

    poly deriv() const {
        if (this->empty()) {
            return poly();
        }
        poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = 1ll * (i + 1) * (*this)[i + 1] % P;
        }
        return res;
    }

    poly integr() const {
        poly res(this->size() + 1);
        comb.init(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = 1ll * (*this)[i] * comb.inv(i + 1) % P;
        }
        return res;
    }

    poly rev() const{
        if(this->empty()){
            return poly();
        }
        poly res = *this;
        while(!res.empty() && res.back() == 0)res.pop_back();
        reverse(res.begin(),res.end());
        return res;
    }

    poly inv(int m) const {
        poly x{power((*this)[0], P - 2)};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }

    poly log(int m) const {
        return (deriv() * inv(m)).integr().trunc(m);
    }

    poly exp(int m) const {
        poly x{1};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }

    poly exp2(int m) const {
        poly f(m), h = deriv();
        h.resize(m);
        f[0] = 1;
        // fn = 1/n(\sum h_k f_{n - 1 - k})
        auto cdq = [&](auto&&self, int l ,int r)->void
        {
            if(l == r){
                if(l == 0)return;
                f[l] = 1ll * f[l] * comb.inv(l) % P;
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
                f[m + i + 1] = f[m + i + 1] + c[i + m - l];
                if(f[m + i + 1] >= P)f[m + i + 1] -= P;
            }
            self(self, m + 1, r);
            return;
        };
        cdq(cdq, 0, m - 1);
        return f;
    }

    poly pow(int k, int m) const {
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

    poly pow(int k, int kmodphiP,int big, int m) const {
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

    poly sqrt(int m) const {
        poly x{Fsqrt((*this)[0])};
        int k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * power(2, P - 2);
        }
        return x.trunc(m);
    }

    poly mulT(poly b) const {
        if (b.size() == 0) {
            return poly();
        }
        int n = b.size();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }

    vector<int> eval(vector<int> x)const 
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

poly lagrange(vector<int>x, vector<int>y)
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

vector<int> valueShift(const vector<int>&v, int c)
{
    int n = v.size() - 1;
    poly a(n + 1),b(n * 2 + 1);
    //fac, invfac
    vector<int>fac(n + 1), invfac(n + 1);
    vector<int>cfac(n * 2 + 2), invcfac(n + 1); // base c - n - 1
    int cbase = c - n - 1;
    cfac[0] = fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = inv(fac[n]);
    for(int i = n - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    for(int i = 1;i <= n * 2 + 1;i++){
        cfac[i] = 1ll * cfac[i - 1] * (i + cbase) % P;
    }
    invcfac[n] = inv(cfac[n]);
    for(int i = n - 1;i >= 0;i--){
        invcfac[i] = 1ll * invcfac[i + 1] * (i + 1 + cbase) % P;
    }

    for(int i = 0;i <= n;i++){
        a[i] = 1ll * v[i] * invfac[i] % P * invfac[n - i] % P;
        if((n - i) % 2 == 1)a[i] = a[i] ? P - a[i] : 0;
    }
    for(int i = 0;i <= n * 2;i++){
        b[i] = inv(c - n + i);
    }
    auto h = a * b;
    vector<int>vc(n + 1);
    for(int i = 0;i <= n;i++){
        vc[i] = 1ll * h[i + n] * cfac[n + i + 1] % P * invcfac[i] % P;
    }
    return vc;
}

poly taylorShift(poly& f, int c)
{
    int n = f.size();
    poly a(n), b(n * 2 - 1);
    vector<int>fac(n + 1), invfac(n + 1);
    fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = inv(fac[n]);
    for(int i = n - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }
    for(int i = 0;i < n;i++){
        a[i] = 1ll * f[i] * fac[i] % P;
    }
    int cp = 1;
    for(int i = 0;i < n;i++){
        b[i] = 1ll * cp * invfac[i] % P;
        cp = 1ll * cp * c % P;
    }
    auto g = a.mulT(b);
    poly res(n);
    for(int i = 0;i < n;i++){
        res[i] = 1ll * g[i] * invfac[i] % P;
    }
    return res;
}

int bostanMori(poly& p, poly& q, i64 n) // calc [x^n] P(x)/Q(x)
{
    int k = q.size() - 1;
    while (n > 0) {
        poly nq = q;
        for (int i = 1; i <= k; i += 2) {
            nq[i] = -nq[i];
            if(nq[i] < 0)nq[i] += P;
        }
        auto np = p * nq;
        nq = q * nq;
        for (int i = 0; i < k; i++) {
            p[i] = np[i * 2 + n % 2];
        }
        for (int i = 0; i <= k; i++) {
            q[i] = nq[i * 2];
        }
        n /= 2;
    }
    return 1ll * p[0] * inv(q[0]) % P;
}

int linearRecurrence(poly a, poly c, i64 n) //a_0 ... a_{k - 1} , c_1 ... c_k
{
    assert(a.size() + 1 == c.size());
    assert(c[0] == 0 || c[0] == P - 1);
    c[0] = -1;
    int k = a.size();
    poly p = (a * (-c)).trunc(k), q = -c;
    return bostanMori(p, q, n);
}

poly berlekampMassey(const vector<int>& s) {
    if (s.empty()) {
        return poly{P - 1};
    }

    poly C{1};   // c[0] = 1
    poly B{1};   
    int L = 0;   
    int m = 1;   // dist from last update
    int b = 1;   // last discrepancy

    for (int n = 0; n < (int)s.size(); n++) {
        int d = 0;
        for (int i = 0; i <= L; i++) {
            if (n - i < 0) break;
            d = (d + 1ll * C[i] * s[n - i]) % P;
        }
        if (d == 0) {
            m++;
            continue;
        }

        poly T = C; 

        // coef = d / b
        int coef = 1LL * d * inv(b) % P;

        // C = C - coef * x^m * B
        if ((int)C.size() < (int)B.size() + m) C.resize(B.size() + m, 0);
        for (int i = 0; i < (int)B.size(); i++) {
            C[i + m] = C[i + m] - 1ll * coef * B[i] % P;
            if(C[i + m] < 0)C[i + m] += P;
        }

        if (2 * L <= n) {
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        } else {
            m++;
        }
    }
    return -C;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>c(n),cc(n),g(n),cg(n);
    for(int i = 0;i < n;i++){
        cin >> c[i];
        c[i]--;
        cc[c[i]]++;
    }
    for(int i = 0;i < n;i++){
        cin >> g[i];
        g[i]--;
        cg[g[i]]++;
    }

    vector<poly>f;
    for(int i = 0;i < n;i++){
        int k = cc[i], m = cg[i];
        if(cc[i] == 0)continue;
        poly g(k + 1);
        for(int i = 0;i <= k;i++){
            g[i] = 1ll * comb.binom(k, i) * comb.binom(m, i) % P * comb.fac(i) % P;
            if(i % 2 == 1)g[i] = -g[i];
            if(g[i] < 0)g[i] += P;
        }
        f.push_back(g);
    }

    auto F = [&](this auto&& mul, int l, int r)->poly
    {
        if(l == r)return f[l];
        int m = l + r >> 1;
        return mul(l, m) * mul(m + 1, r);
    }(0, f.size() - 1);


    int ans = 0;
    for(int i = 0;i <= n;i++){
        ans = (ans + 1ll * comb.fac(n - i) * F[i]) % P;
    }
    ans = 1ll * ans * comb.invfac(n) % P;
    cout << ans << endl;
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