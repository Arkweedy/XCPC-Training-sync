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
    int n,q;
    cin>>n>>q;
    int sum = 0;
    vector<vector<int>>a(n,vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin>>a[i][j];
            sum += a[i][j];
        }
    }
    int m = n * 2 + 2;
    vector<Z>p(m);//
    vector<ull>msk(m);
    for(int i = 0;i < m;i++){
        for(int j = 0;j < n;j++){
            int x,y;
            cin>>x>>y;
            x--,y--;
            msk[i] |= 1ull << x * n + y;
        }
    }
    Z invs = Z(1) / sum;
    vector<Z>exp(sum + 1);
    for(int i = 1;i <= sum; i++){
        exp[i] = Z(sum) / i;
    }
    vector<Z>ans(1 << m);
    vector<int>vs(1 << m);
    auto dfs = [&](auto&&self ,int p, int gmask, ull cmask, vector<Z>dp)->void
    {
        if(p == m){
            vs[gmask] = true;
            for(int i = 0;i <= sum;i++){
                ans[gmask] -= exp[i] * dp[i];
            }
            return;
        }
        self(self, p + 1, gmask, cmask, dp);
        int ngmask = gmask | 1 << p;
        ull ncmask = cmask | msk[p];
        ull mcmask = ncmask ^ cmask;
        for(int i = 0;i < n * n;i++){
            if(mcmask >> i & 1){
                int x = i / n, y = i % n;
                for(int j = sum - a[x][y];j >= 0;j--){
                    dp[j + a[x][y]] += -1 * dp[j];
                }
            }
        }
        self(self,p + 1,ngmask,ncmask,dp);
        return;
    };

    auto get = [&](int p)->Z // calc \sum min(p)
    {
        if(vs[p])return ans[p];
        vector<Z>dp(sum + 1);
        dp[0] = 1;
        ull mask = 0;
        for(int i = 0;i < m;i++){
            if(p >> i & 1){
                mask |= msk[i];
            }
        }
        for(int i = 0;i < n * n;i++){
            if(mask >> i & 1){
                int x = i / n, y = i % n;
                for(int j = sum - a[x][y];j >= 0;j--){
                    dp[j + a[x][y]] += -1 * dp[j];
                }
            }
        }
        Z res = 0;
        for(int i = 0;i <= sum;i++){
            res += exp[i] * dp[i];
        }
        ans[p] = -res;
        vs[p] = true;
        return -res;
    };

    vector<Z>dp(sum + 1);
    dp[0] = 1;
    dfs(dfs, 0,0,0, dp);

    while(q--){
        int p;
        cin>>p;
        cout<<get(p)<<'\n';
    }
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