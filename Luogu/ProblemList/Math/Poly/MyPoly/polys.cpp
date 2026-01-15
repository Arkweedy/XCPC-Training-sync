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
        return (a - a / b * b).trunc(b.size() - 1);
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


void solve()
{
    int n;
    cin >> n;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
    }
    auto f = lagrange(x, y);
    cerr << f.size() << endl;
    for(int i = 0;i < n;i++){
        cout << f[i] << " ";
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