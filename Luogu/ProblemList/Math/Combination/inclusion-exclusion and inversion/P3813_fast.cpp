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
//constexpr int P = 998244353;
constexpr int P = 1000000007;
using Z = MInt<P>;

void solve()
{
    int h, w, m, n;
    cin>>h>>w>>m>>n;
    vector<array<int,4>>a(n);
    vector<int>v(n);
    for(int i = 0;i < n;i++){
        auto& [x,y,l,r] = a[i];
        cin>>x>>y>>l>>r>>v[i];
        x--, y--;
    }

    int len = 1 << n;
    array<int,4>nar = {-1,-1,-1,-1};

    auto intersect = [&](const array<int,4>& a, const array<int,4>& b)->array<int,4>
    {
        int xl = max(a[0], b[0]), xr = min(a[2], b[2]);
        int yl = max(a[1], b[1]), yr = min(a[3], b[3]);
        if(xl >= xr || yl >= yr){
            return {-1,-1,-1,-1};
        }
        else{
            return {xl,yl,xr,yr};
        }
    };

    vector<int>sqr(len, 0);
    vector<int>ss(len, 0);
    vector<array<int,4>>rec(len);
    rec[0] = {0,0,h,w};
    ss[0] = 0;
    sqr[0] = 0;
    //O(2^n)
    for(int j = 0;j < n;j++){
        for(int i = 0;i < (1 << j + 1);i++){
            if(i >> j & 1){
                rec[i] = intersect(rec[i ^ (1 << j)], a[j]);
                ss[i] = (rec[i][2] - rec[i][0]) * (rec[i][3] - rec[i][1]);//nar = 0
                sqr[i] = (popcount(uint(i)) % 2 == 1 ? 1 : -1) * ss[i];
            }
        }
    }

    for(int i = 1;i < n;i++){
        rec[i] = intersect(rec[i - (i & -i)], a[__lg(i & -i)]);
        ss[i] = (rec[i][2] - rec[i][0]) * (rec[i][3] - rec[i][1]);//nar = 0
        sqr[i] = (popcount(uint(i)) % 2 == 1 ? 1 : -1) * ss[i];
    }

    //O(n*2^n)
    for(int j = 0;j < n;j++){
        for(int i = 0;i < len;i++){
            if(i >> j & 1){
                sqr[i] += sqr[i ^ (1 << j)];
            }
        }
    }

    Z ans = 1;
    vector<int>uv = v;
    sort(uv.begin(),uv.end());
    uv.erase(unique(uv.begin(),uv.end()), uv.end());
    //O(2^n) (only whole block -> O(2^n), not O(3^n)) \sum_{i = 1}^n i2^i = 3^n
    for(auto i : uv){
        int less = 0, eq = 0;
        for(int j = 0;j < n;j++){
            if(v[j] < i){
                less |= (1 << j);
            }
            else if(v[j] == i){
                eq |= (1 << j);
            }
        }
        Z res = 0;
        int all = sqr[less | eq] - sqr[less];
        for(int s = eq;1;s = (s - 1) & eq){
            int dif = popcount(uint(s));
            int neg = sqr[less | s] - sqr[less];
            res += (dif % 2 == 0 ? 1 : -1) * power(Z(i - 1), neg) * power(Z(i), all - neg);
            if(s == 0)break;
        }
        ans *= res;
    }
    ans *= power(Z(m), h * w - sqr[(1 << n) - 1]);
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