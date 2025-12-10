// ====== 依赖：你提供的多项式与数论模板（保持原样即可） ======
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) if (b & 1) res *= a;
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(int(x % getMod()))} {}
    static int Mod;
    constexpr static int getMod() { return P > 0 ? P : Mod; }
    constexpr static void setMod(int Mod_) { Mod = Mod_; }
    constexpr int norm(int v) const { if (v < 0) v += getMod(); if (v >= getMod()) v -= getMod(); return v; }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr MInt operator-() const { MInt r; r.x = norm(getMod() - x); return r; }
    constexpr MInt inv() const { assert(x); return power(*this, getMod() - 2); }
    constexpr MInt& operator*=(MInt r)& { x = 1LL * x * r.x % getMod(); return *this; }
    constexpr MInt& operator+=(MInt r)& { x = norm(x + r.x); return *this; }
    constexpr MInt& operator-=(MInt r)& { x = norm(x - r.x); return *this; }
    constexpr MInt& operator/=(MInt r)& { return *this *= r.inv(); }
    friend constexpr MInt operator*(MInt a, MInt b){ a*=b; return a; }
    friend constexpr MInt operator+(MInt a, MInt b){ a+=b; return a; }
    friend constexpr MInt operator-(MInt a, MInt b){ a-=b; return a; }
    friend constexpr MInt operator/(MInt a, MInt b){ a/=b; return a; }
    friend istream& operator>>(istream& is, MInt& a){ i64 v; is>>v; a=MInt(v); return is; }
    friend ostream& operator<<(ostream& os, const MInt& a){ return os<<a.val(); }
    friend constexpr bool operator==(MInt a, MInt b){ return a.val()==b.val(); }
    friend constexpr bool operator!=(MInt a, MInt b){ return a.val()!=b.val(); }
};
template<> int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z = MInt<P>;

std::vector<int> rev;
template<int P> std::vector<MInt<P>> roots{0,1};

template<int P>
constexpr MInt<P> findPrimitiveRoot() {
    MInt<P> i = 2;
    int k = __builtin_ctz(P - 1);
    while (true) {
        if (power(i, (P - 1) / 2) != 1) break;
        i += 1;
    }
    return power(i, (P - 1) >> k);
}
template<int P> constexpr MInt<P> primitiveRoot = findPrimitiveRoot<P>();
template<> constexpr MInt<998244353> primitiveRoot<998244353> {31};

template<int P>
constexpr void dft(std::vector<MInt<P>>& a){
    int n = (int)a.size();
    if ((int)rev.size() != n){
        int k = __builtin_ctz(n) - 1;
        rev.assign(n, 0);
        for (int i=0;i<n;i++) rev[i] = (rev[i>>1]>>1) | ((i&1)<<k);
    }
    for (int i=0;i<n;i++) if (rev[i]<i) swap(a[i], a[rev[i]]);
    if ((int)roots<P>.size() < n){
        int k = __builtin_ctz((int)roots<P>.size());
        roots<P>.resize(n);
        while ((1<<k) < n){
            auto e = power(primitiveRoot<P>, 1 << (__builtin_ctz(P-1) - k - 1));
            for (int i=1<<(k-1); i<(1<<k); ++i){
                roots<P>[2*i] = roots<P>[i];
                roots<P>[2*i+1] = roots<P>[i]*e;
            }
            ++k;
        }
    }
    for (int k=1; k<n; k<<=1){
        for (int i=0;i<n;i+=2*k){
            for (int j=0;j<k;++j){
                auto u=a[i+j], v=a[i+j+k]*roots<P>[k+j];
                a[i+j]=u+v; a[i+j+k]=u-v;
            }
        }
    }
}
template<int P>
constexpr void idft(std::vector<MInt<P>>& a){
    int n = (int)a.size();
    reverse(a.begin()+1, a.end());
    dft(a);
    MInt<P> inv = (1 - P) / n;
    for (int i=0;i<n;++i) a[i] *= inv;
}

template<int P=998244353>
struct Poly : public std::vector<MInt<P>>{
    using Value = MInt<P>;
    using Base = std::vector<Value>;
    Poly():Base(){} explicit constexpr Poly(int n):Base(n){}
    explicit constexpr Poly(const Base& a):Base(a){}
    constexpr Poly(const std::initializer_list<Value>& a):Base(a){}
    template<class It, class = std::_RequireInputIter<It>>
    explicit constexpr Poly(It f, It l): Base(f,l){}
    template<class F> explicit constexpr Poly(int n, F fn):Base(n){ for (int i=0;i<n;i++) (*this)[i]=fn(i); }

    constexpr Poly shift(int k) const {
        if (k>=0){ Poly b=*this; b.insert(b.begin(), k, 0); return b; }
        if ((int)this->size() <= -k) return Poly();
        return Poly(this->begin()+(-k), this->end());
    }
    constexpr Poly trunc(int k) const { Poly f=*this; f.resize(k); return f; }

    friend constexpr Poly operator+(const Poly& a, const Poly& b){
        Poly r(max(a.size(), b.size()));
        for (int i=0;i<(int)a.size();++i) r[i]+=a[i];
        for (int i=0;i<(int)b.size();++i) r[i]+=b[i];
        return r;
    }
    friend constexpr Poly operator-(const Poly& a, const Poly& b){
        Poly r(max(a.size(), b.size()));
        for (int i=0;i<(int)a.size();++i) r[i]+=a[i];
        for (int i=0;i<(int)b.size();++i) r[i]-=b[i];
        return r;
    }
    friend constexpr Poly operator-(const Poly& a){
        Poly r((int)a.size());
        for (int i=0;i<(int)r.size();++i) r[i] = -a[i];
        return r;
    }
    friend constexpr Poly operator*(Poly a, Poly b){
        if (a.empty() || b.empty()) return Poly();
        if (a.size() < b.size()) swap(a, b);
        int n=1, tot=(int)a.size() + (int)b.size() - 1;
        while (n<tot) n<<=1;
        if (((P-1)&(n-1))!=0 || b.size()<128){
            Poly c(tot);
            for (int i=0;i<(int)a.size();++i)
                for (int j=0;j<(int)b.size();++j)
                    c[i+j] += a[i]*b[j];
            return c;
        }
        a.resize(n); b.resize(n);
        dft(a); dft(b);
        for (int i=0;i<n;++i) a[i] *= b[i];
        idft(a);
        a.resize(tot);
        return a;
    }
    friend constexpr Poly operator*(Value a, Poly b){ for (auto &x: b) x*=a; return b; }
    friend constexpr Poly operator*(Poly a, Value b){ for (auto &x: a) x*=b; return a; }
    friend constexpr Poly operator/(Poly a, Value b){ for (auto &x: a) x/=b; return a; }

    constexpr Poly& operator+=(Poly b){ return (*this)=(*this)+b; }
    constexpr Poly& operator-=(Poly b){ return (*this)=(*this)-b; }
    constexpr Poly& operator*=(Poly b){ return (*this)=(*this)*b; }
    constexpr Poly& operator*=(Value b){ return (*this)=(*this)*b; }
    constexpr Poly& operator/=(Value b){ return (*this)=(*this)/b; }

    constexpr Poly deriv() const {
        if (this->empty()) return Poly();
        Poly r(this->size()-1);
        for (int i=0;i+1<(int)this->size();++i) r[i] = (i+1)*(*this)[i+1];
        return r;
    }
    constexpr Poly integr() const {
        Poly r(this->size()+1);
        for (int i=0;i<(int)this->size();++i) r[i+1] = (*this)[i] / (i+1);
        return r;
    }
    constexpr Poly inv(int m) const {
        Poly x{(*this)[0].inv()};
        int k=1;
        while (k<m){
            k<<=1;
            x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }
    constexpr Poly log(int m) const { return (deriv()*inv(m)).integr().trunc(m); }
    constexpr Poly exp(int m) const {
        Poly x{1}; int k=1;
        while (k<m){
            k<<=1;
            x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }
    constexpr Poly pow(int k, int m) const {
        int i=0;
        while (i<(int)this->size() && (*this)[i]==0) ++i;
        if ( i==(int)this->size() || 1LL*i*k >= m ) return Poly(m);
        Value v = (*this)[i];
        auto f = shift(-i) * v.inv();
        return (f.log(m-i*k)*k).exp(m-i*k).shift(i*k) * power(v, k);
    }
    constexpr Poly sqrt(int m) const {
        Poly x{1}; int k=1;
        while (k<m){
            k<<=1;
            x = (x + (trunc(k)*x.inv(k)).trunc(k)) * CInv<2,P>;
        }
        return x.trunc(m);
    }
    constexpr Poly mulT(Poly b) const {
        if (b.empty()) return Poly();
        int n = (int)b.size();
        reverse(b.begin(), b.end());
        return ((*this)*b).shift(-(n-1));
    }
    constexpr vector<Value> eval(vector<Value> x) const {
        if (this->empty()) return vector<Value>(x.size(), 0);
        const int n = max((int)x.size(), (int)this->size());
        vector<Poly> q(4*n);
        vector<Value> ans(x.size());
        x.resize(n);
        function<void(int,int,int)> build = [&](int p,int l,int r){
            if (r-l==1) q[p]=Poly{1, -x[l]};
            else{
                int m=(l+r)>>1;
                build(p<<1,l,m); build(p<<1|1,m,r);
                q[p] = q[p<<1]*q[p<<1|1];
            }
        };
        build(1,0,n);
        function<void(int,int,int,const Poly&)> work = [&](int p,int l,int r,const Poly& num){
            if (r-l==1){ if (l<(int)ans.size()) ans[l]=num[0]; }
            else{
                int m=(l+r)>>1;
                work(p<<1,l,m, num.mulT(q[p<<1|1]).trunc(m-l));
                work(p<<1|1,m,r, num.mulT(q[p<<1]).trunc(r-m));
            }
        };
        work(1,0,n, mulT(q[1].inv(n)));
        return ans;
    }
};

template<int P=998244353>
Poly<P> berlekampMassey(const Poly<P>& s){
    Poly<P> c, oldC; int f=-1;
    for (int i=0;i<(int)s.size();++i){
        auto delta = s[i];
        for (int j=1;j<= (int)c.size(); ++j) delta -= c[j-1]*s[i-j];
        if (delta==0) continue;
        if (f==-1){ c.resize(i+1); f=i; }
        else{
            auto d=oldC; d*=-1; d.insert(d.begin(), 1);
            MInt<P> df1 = 0;
            for (int j=1;j<= (int)d.size(); ++j) df1 += d[j-1]*s[f+1-j];
            auto coef = delta / df1;
            d *= coef;
            Poly<P> zeros(i-f-1); zeros.insert(zeros.end(), d.begin(), d.end()); d = zeros;
            auto tmp=c; c+=d;
            if (i - (int)tmp.size() > f - (int)oldC.size()){ oldC=tmp; f=i; }
        }
    }
    c*=-1; c.insert(c.begin(), 1);
    return c;
}

template<int P=998244353>
MInt<P> linearRecurrence(Poly<P> p, Poly<P> q, i64 n){
    int m=(int)q.size()-1;
    while (n>0){
        auto newq=q;
        for (int i=1;i<=m;i+=2) newq[i]*=-1;
        auto newp=p*newq; newq=q*newq;
        for (int i=0;i<m;++i) p[i] = newp[i*2 + (n&1)];
        for (int i=0;i<=m;++i) q[i] = newq[i*2];
        n >>= 1;
    }
    return p[0]/q[0];
}

struct Comb{
    int n; vector<Z> _fac,_invfac,_inv;
    Comb():n(0),_fac{1},_invfac{1},_inv{0}{} Comb(int n):Comb(){init(n);}
    void init(int m){
        if (m<=n) return;
        _fac.resize(m+1); _invfac.resize(m+1); _inv.resize(m+1);
        for (int i=n+1;i<=m;++i) _fac[i] = _fac[i-1]*i;
        _invfac[m] = _fac[m].inv();
        for (int i=m;i>n;--i){ _invfac[i-1]=_invfac[i]*i; _inv[i]=_invfac[i]*_fac[i-1]; }
        n = m;
    }
    Z fac(int m){ if (m>n) init(2*m); return _fac[m]; }
    Z invfac(int m){ if (m>n) init(2*m); return _invfac[m]; }
    Z inv(int m){ if (m>n) init(2*m); return _inv[m]; }
    Z binom(int n,int m){ if (n<m || m<0) return 0; return fac(n)*invfac(m)*invfac(n-m); }
} comb;

using poly = Poly<P>;

// ====== 树上路径长度统计（O(n log n)）板子开始 ======

struct TreePathsAllDistances {
    int n;
    vector<vector<int>> g;

    vector<int> fa, dep, siz, heavy, top; // HLD 基本信息
    vector<poly> sub, Plight;            // sub[v]：整棵子树深度分布   Plight[v]：v 的“轻部分+自点”分布
    vector<Z> dist;                       // 答案：dist[k] = 长度为 k 的路径数
    const Z inv2 = CInv<2, P>;

    TreePathsAllDistances(int n): n(n), g(n), fa(n,-1), dep(n,0), siz(n,0),
                                  heavy(n,-1), top(n,-1), sub(n), Plight(n),
                                  dist(n, 0) {}

    inline void add_edge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }

    // 1) 统计 size 并选重儿子
    void dfs_sz(int u, int p){
        fa[u]=p; siz[u]=1; int mx=0;
        for (int v: g[u]) if (v!=p){
            dep[v]=dep[u]+1;
            dfs_sz(v, u);
            siz[u]+=siz[v];
            if (siz[v]>mx){ mx=siz[v]; heavy[u]=v; }
        }
    }

    // 2) 构造 sub[u]；构造 Plight[u]；同时加上“同点内部”的贡献
    poly merge_add_pairs(const vector<poly>& arr, int l, int r){
        if (l>=r) return {};
        if (l+1==r) return arr[l];
        int m=(l+r)>>1;
        poly L = merge_add_pairs(arr, l, m);
        poly R = merge_add_pairs(arr, m, r);
        if (!L.empty() && !R.empty()){
            poly C = L * R;            // 跨两边的不同轻儿子对
            add_to_dist(C);
        }
        return L + R;
    }

    void add_to_dist(const poly& a){
        int up = min<int>(n, a.size());
        for (int i=1;i<up;++i) dist[i] += a[i]; // i=0 对应同点，忽略
    }

    void dfs_poly(int u, int p){
        // 先算所有子节点
        for (int v: g[u]) if (v!=p) dfs_poly(v, u);

        // sub[u] = 合并所有子树 + 自点
        sub[u] = poly{1}; // 自点
        for (int v: g[u]) if (v!=p){
            // 把 sub[v] 向右移 1（过一条边）
            poly sh = sub[v].shift(1);
            if (sub[u].size() < sh.size()) sub[u].resize(sh.size());
            for (int i=0;i<(int)sh.size();++i) sub[u][i] += sh[i];
        }

        // 轻儿子集合
        vector<poly> childs;
        for (int v: g[u]) if (v!=p && v!=heavy[u]){
            childs.push_back( sub[v].shift(1) );
        }

        // Plight[u] = 1 + sum(轻儿子.shift(1))
        Plight[u] = poly{1};
        for (auto &q: childs){
            if (Plight[u].size() < q.size()) Plight[u].resize(q.size());
            for (int i=0;i<(int)q.size();++i) Plight[u][i] += q[i];
        }

        // “同点内部”贡献：
        // 1) v 本身 与 轻部分的配对：距离 = 轻部分多项式（去掉常数项）
        add_to_dist(Plight[u]); // 常数项是 1，对 dist[0] 无影响；我们 add_to_dist 从 1 开始取

        // 2) 不同轻儿子之间配对：用分治合并（每层只做一次卷积）
        if (!childs.empty()) merge_add_pairs(childs, 0, (int)childs.size());
    }

    // 3) HLD 链剖
    void dfs_hld(int u, int tp){
        top[u]=tp;
        if (heavy[u]!=-1) dfs_hld(heavy[u], tp);
        for (int v: g[u]) if (v!=fa[u] && v!=heavy[u]) dfs_hld(v, v);
    }

    // 4) 链内 CDQ：跨半区做一次卷积
    void cdq_chain(const vector<int>& nds, int L, int R){
        if (R-L<=1) return;
        int M=(L+R)>>1;

        cdq_chain(nds, L, M);
        cdq_chain(nds, M, R);

        // A = sum_{i in [L,M)} Plight[i] << (M-1-i)
        // B = sum_{j in [M,R)} Plight[j] << (j-M+1)
        poly A, B;
        for (int i=L;i<M;++i){
            int sh = (M-1 - i);
            const poly& p = Plight[nds[i]];
            if (p.empty()) continue;
            if (A.size() < p.size()+sh) A.resize(p.size()+sh);
            for (int k=0;k<(int)p.size();++k) A[k+sh] += p[k];
        }
        for (int j=M;j<R;++j){
            int sh = (j - M + 1);
            const poly& p = Plight[nds[j]];
            if (p.empty()) continue;
            if (B.size() < p.size()+sh) B.resize(p.size()+sh);
            for (int k=0;k<(int)p.size();++k) B[k+sh] += p[k];
        }
        if (!A.empty() && !B.empty()){
            poly C = A * B;
            add_to_dist(C);
        }
    }

    void work(int root = 0){
        dfs_sz(root, -1);
        dfs_poly(root, -1);
        dfs_hld(root, root);

        // 枚举每条链，把这条链上的节点收集到向量里，然后做 CDQ
        vector<int> vis(n, 0);
        for (int u=0; u<n; ++u){
            if (top[u]==u){ // 链头
                vector<int> nds;
                int x=u;
                while (x!=-1){
                    nds.push_back(x);
                    vis[x]=1;
                    x = heavy[x];
                }
                cdq_chain(nds, 0, (int)nds.size());
            }
        }
    }

    // 返回 dist[1..n-1]
    vector<Z> get_dist() const { return dist; }
};

void solve()
{
    int n;
    cin>>n;
    TreePathsAllDistances solver(n);
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        solver.add_edge(u,v);
    }
    solver.work(0); // 以 0 为根（不影响结果）

    auto d = solver.get_dist();

    poly g(n + 1),h(n + 1);
    for(int i = 0;i <= n - 2;i++){
        g[i] = d[i + 1] * comb.fac(n - i - 2);
    }
    for(int i = 0;i <= n;i++){
        h[i] = comb.invfac(i);
    }
    auto f = g * h;
    for(int i = 0;i <= n - 2;i++){
        f[i] *= comb.invfac(n - i - 2) * comb.fac(i);
    }
    f[n - 1] = f[n] = 0;
    for(int i = 1;i <= n;i++){
        cout<<f[i]<<" ";
    }
    cout<<endl;
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
