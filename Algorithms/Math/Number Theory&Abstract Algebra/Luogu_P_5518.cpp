#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


constexpr int N = 100001;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;
vector<int>lpfp;
vector<int>phi;

void seive()
{
    isprime.set();
    mu.resize(N + 1);
    lpfp.resize(N + 1);
    phi.resize(N + 1);
    isprime[0] = isprime[1] = 0;
    phi[1] = lpfp[1] = mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            mu[i] = -1;
            lpfp[i] = i;
            phi[i] = i - 1;
        }
        for (auto& p : prime) {//p = lpf[i * p]
            if (p * i > N)
                break;
            isprime.flip(i * p);

            if (i % p == 0) {
                lpfp[i * p] = lpfp[i] * p;
                if (lpfp[i * p] == i * p) {//p ^ k
                    phi[i * p] = lpfp[i * p] - lpfp[i];//phi(p^k) = p^k - p^(k-1)
                }
                else {//p^k * ...
                    phi[i * p] = phi[lpfp[i * p]] * phi[(i * p) / lpfp[i * p]];
                }

                mu[i * p] = 0;
                break;
            }
            else {
                lpfp[i * p] = p;
                phi[i * p] = phi[i] * phi[p];
                mu[i * p] = mu[i] * (-1);
            }
        }
    }
}
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
 template<i64 P>
 struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
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
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
    };
 template<>
 i64 MLong<0LL>::Mod = i64(1E18) + 9;
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
 template<>
 int MInt<0>::Mod = 998244353;
 template<int V, int P>
 constexpr MInt<P> CInv = MInt<P>(V).inv();
 
template<>
int MInt<1>::Mod = 1000000007;

using Z = MInt<0>;
using Zphi = MInt<1>;

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

vector<Z>idpowmud;
vector<Z>pmidpowmud;
vector<Z>id2powmud;
vector<Z>pmid2powmud;
vector<Z>idid;
vector<Z>pidid;
vector<Z>idpphi;
vector<Z>pidpphi;
vector<int>psphi;

vector<Z>pmidpowmudinv;
vector<Z>pidpphiinv;

void init()
{
    idpowmud.resize(N + 1,1);
    pmidpowmud.resize(N + 1,1);
    id2powmud.resize(N + 1,1);
    pmid2powmud.resize(N + 1,1);
    idid.resize(N + 1,1);
    pidid.resize(N + 1,1);
    idpphi.resize(N + 1,1);
    pidpphi.resize(N + 1,1);
    psphi.resize(N + 1,1);
    pmidpowmudinv.resize(N + 1,1);
    pidpphiinv.resize(N + 1,1);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j * i <= N;j++){
            if(mu[j] == 0){
                idpowmud[i * j] *= 1;
            }
            else if(mu[j] == 1){
                idpowmud[i * j] *= i;
            }
            else {
                idpowmud[i * j] *= comb.inv(i);
            }
        }
    }
    for(int i = 1;i <= N;i++){
        idid[i] = power(Z(i),i);
        id2powmud[i] = power(idpowmud[i],1ll*i*i);
        idpphi[i] = power(Z(i),phi[i]);
    }
    for(int i = 1;i <= N;i++){
        pmidpowmud[i] = idpowmud[i] * pmidpowmud[i-1];
        pmid2powmud[i] = id2powmud[i] * pmid2powmud[i-1];
        pidid[i] = idid[i] * pidid[i-1];
        pidpphi[i] = idpphi[i] * pidpphi[i-1];
        psphi[i] = (phi[i] + psphi[i-1]) % (Z::Mod - 1);
        pmidpowmudinv[i] = pmidpowmud[i].inv();
        pidpphiinv[i] = pidpphi[i].inv();
    }
    // for(int i = 1;i <= 10;i++){
    //     cerr<<id2powmud[i]<<" "<<pmid2powmud[i]<<endl;
    // }
}

void solve()
{
    int a,b,c;
    cin>>a>>b>>c;
    auto calcgcd = [&](int x,int y)->Z
    {
        Z res = 1;
        for(int l = 1,r;l <= min(x,y);l = r + 1){
            int r1 = x / (x / l),r2 = y/(y / l);
            r = min(r1,r2);
            res *= power(pmidpowmud[r]/pmidpowmud[l-1],1ll * (x / l) * (y / l));
        }
        //cerr<<"calcgcd("<<x<<","<<y<<") = "<<res<<endl;
        return res;
    };
    auto calct1 = [&]()->Z
    {
        return power(comb.fac(a),1ll * b * c) * power(comb.fac(b),1ll * a * c)
             / power(calcgcd(a,b),c) / power(calcgcd(a,c),b);
    };
    auto calcf = [&](int x)->int
    {
        return 1ll * x * (x + 1) / 2 % (Z::Mod-1);
    };
    auto calcf2 = [&](int x,int y)->Z
    {
        Z res = 1;
        for(int l = 1,r;l <= min(x,y);l=r+1){
            int r1 = x/(x/l),r2 = y/(y/l);
            r = min(r1,r2);
            res *= power(pmid2powmud[r]/pmid2powmud[l-1],(1ll * calcf(x/l)*calcf(y/l)));
        }
        //cerr<<"calcf2("<<x<<","<<y<<") = "<<res<<endl;
        return res;
    };
    auto calcid = [&](int x, int y, int z)->Z
    {
        return power(pidid[x],1ll * calcf(y) *calcf(z));
    };
    auto calct2 = [&]()->Z
    {
        return calcid(a,b,c)*calcid(b,a,c) / power(calcf2(a,b),calcf(c)) / power(calcf2(a,c),calcf(b));
    };

    auto calcphi = [&](int l ,int r)->int
    {
        return (psphi[r]-psphi[l-1] >= 0) ? psphi[r]-psphi[l-1] : psphi[r]-psphi[l-1] + Z::Mod - 1;
    };
    auto calcs = [&](int x,int y, int z)->Z
    {
        Z res = 1;
        for(int l = 1,r;l <= min({x,y,z});l = r + 1){
            int r1 = x/(x/l),r2 = y/(y/l),r3 = z/(z/l);
            r = min({r1,r2,r3});
            res *= power(comb.fac(x/l),1ll * (y/l) * (z/l) % (Z::Mod-1) * calcphi(l,r) % (Z::Mod-1))
                 * power(pidpphi[r] * pidpphiinv[l-1],1ll * (x/l) * (y/l) %(Z::Mod-1) * (z/l)% (Z::Mod-1));
        }
        return res;
    };
    auto calcx = [&](int x,int y,int z)->Z
    {
        Z res = 1;
        for(int l = 1,r;l <= min({x,y,z});l = r + 1){
            int r1 = x/(x/l),r2 = y/(y/l),r3 = z/(z/l);
            r = min({r1,r2,r3});
            res *= power(pidpphi[r] * pidpphiinv[l-1],1ll * (x/l) * (y/l) % (Z::Mod-1) * (z/l) % (Z::Mod-1));
        }
        return res;
    };
    auto calcinner = [&](int x, int y)->Z //x = x / k, y = y / k
    {
        Z res = 1;
        for(int l = 1,r;l <= min(x,y);l = r + 1){
            int r1 = x / (x / l),r2 = y / (y / l);
            r = min(r1,r2);
            res *= power(pmidpowmud[r] * pmidpowmudinv[l-1],1ll*(x/l)*(y/l) % (Z::Mod - 1));
        }
        return res;
    };
    auto calcdx = [&](int x,int y,int z)->Z
    {
        Z res = 1;
        for(int l = 1,r;l <= min({x,y,z});l = r + 1){
            int r1 = x / (x / l),r2 = y / (y / l), r3 = z / (z / l);
            r = min({r1,r2,r3});
            res *= power(calcinner(x / l, y / l), 1ll * calcphi(l,r) * (z / l) % (Z::Mod - 1));
        }
        return res;
    };
    auto calcg = [&](int x,int y, int z)->Z
    {
        return calcdx(x,y,z)*calcx(x,y,z);
    };
    auto calct3 = [&]()->Z
    {
        return calcs(a,b,c)*calcs(b,a,c)/calcg(a,b,c)/calcg(a,c,b);
    };
    cout<<calct1()<<" "<<calct2()<<" "<<calct3()<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    int p;
    cin>>p;
    Z::setMod(p);
    Zphi::setMod(p-1);
    seive();
    init();
    while(tt--){
        solve();
    }
    #ifdef LOCAL_DEBUG
        system("pause");
    #endif
    return 0;
}