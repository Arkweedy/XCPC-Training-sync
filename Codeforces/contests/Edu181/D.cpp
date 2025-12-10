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
//using Z = MInt<P>;
using Z = double;

template<typename T>
class bit //1 base
{
    int n;
    int upper;
    vector<T>tree;

    inline static const int lowbit(const int x)
    {
        return x & -x;
    }

public:
    bit(vector<T>& a)
    {
        n = a.size() - 1;
        tree = a;
        for (int i = 1; i <= n; i++) {
            if (i + lowbit(i) <= n) {
                tree[i + lowbit(i)] *= tree[i];
            }
        }
        upper = n;
        if (lowbit(upper) != upper) {
            while (upper != lowbit(upper)) {
                upper -= lowbit(upper);
            }
            upper <<= 1;
        }
    }

    void print()
    {
        for(int i = 0;i < n;i++){
            cerr<<tree[i]<<" ";
        }
        cerr<<endl;
    }

    void add(int p, T x)
    {
        while (p <= n) {
            tree[p] *= x;
            p += lowbit(p);
        }
    }

    T qry(int r)
    {
        T res = 1;
        while (r != 0) {
            res *= tree[r];
            r -= lowbit(r);
        }
        return res;
    }

    T qry(int l, int r)
    {
        if (l > 0)
            return qry(r) / qry(l - 1);
        else
            return qry(r);
    }

    int findleq(T v)const //前缀和小于等于的最大位置
    {
        int p = 0;
        T sum = 0;
        for (int len = upper; len != 0; len >>= 1) {
            if (len + p <= n && sum + tree[len + p] <= v) {
                p += len;
                sum += tree[p];
            }
        }
        return p;
    }

    int findl(T v)const //严格小的最大位置
    {
        int r = upper;
        int p = 0;
        T sum = 0;
        for (int len = upper; len != 0; len >>= 1) {
            if (len + p <= n && sum + tree[len + p] < v) {
                p += len;
                sum += tree[p];
            }
        }
        return p;
    }
};

void solve()
{
    int n, m;
    cin>>n>>m;
    vector<array<int,4>>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3];
    }
    sort(a.begin(),a.end());
    a.push_back({0,0,0,0});
    vector<tuple<int,int,Z>>seg;
    int L = 0, R = 0;
    Z pp = 0;
    for(int i = 0;i <= n;i++){
        const auto& [l,r,p,q] = a[i];
        if(l != L || r != R){
            if(L != 0)seg.push_back({L,R,pp});
            L = l;
            R = r;
            pp = Z(p) / q;
        }
        else{
            pp = pp + Z(p) / q - pp * (Z(p) / q);
        }
    }
    int len = seg.size();
    vector<Z>dp(m + 1);
    vector<Z>rdp(m + 2, 1);//rdp = \prod 1/(1 - p)
    vector<Z>dpfac(len, 1);
    rdp[0] = dp[0] = 1;
    // dp[r] += dp[l - 1] * p/ \prod(1-p)

    sort(seg.begin(),seg.end(), [&](const tuple<int,int,Z>& i , const tuple<int,int,Z>& j)->bool
    {
        const auto&[il,ir,ip] = i;
        const auto&[jl,jr,jp] = j;
        return il == jl ? ir > jr : il < jl; 
    });
    
    for(int i = 0;i < n;i++){
        const auto& [l,r,p,q] = a[i];
        Z A = Z(p) / q;
        Z B = 1 - A;
        rdp[l] *= B;
        rdp[r + 1] /= B;
    }
    for(int i = 1;i <= m;i++){
        rdp[i] *= rdp[i - 1];
    }
    for(int i = 0;i < len;i++){
        const auto& [l,r,p] = seg[i];
        dpfac[i] *= rdp[l] * rdp[r];
    }
    vector<Z>tmp(m + 5, 1);
    bit<Z>t(tmp);
    for(int i = 0;i < seg.size();i++){
        const auto& [l,r,p] = seg[i];
        dpfac[i] /= t.qry(m + 1 - r);
        t.add(m + 1 - r,1 - p);
    }

    
    
    cerr<<len<<endl;
    for(int i = 0;i < len;i++){
        const auto& [l,r,p] = seg[i];
        cerr<<l<<" "<<r<<" "<<p<<" "<<dpfac[i]<<endl;
        Z A = p;
        Z B = 1 - A;
        dp[r] += dp[l - 1] * A / B * dpfac[i];
    }
    
    for(int i = 0;i <= m;i++){
        cerr<<rdp[i]<<" ";
    }
    cerr<<endl;
    for(int i = 0;i <= m;i++){
        cerr<<dp[i]<<" ";
    }
    cerr<<endl;
    cout<<dp[m]<<endl;
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