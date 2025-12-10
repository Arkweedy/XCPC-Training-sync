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

constexpr int N = 1e5 + 10;
vector<int>prime;
bitset<N + 1>isprime;

void seive()
{
    isprime.set();
    isprime[1] = 0;
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            prime.push_back(i);
        }

        for(auto p : prime){
            if(i * p > N)break;
            isprime[i * p].flip();
            if(i % p == 0)break;
        }
    }
}

Z min_25(ll n)
{
    int m = floorl(sqrtl(n));
    //f(p ^ c) = p xor c
    // g(p) = p,  h(p) = 1
    // \sum_prime f(p) = \sum_prime g(p) - h(p) + 2

    vector<Z>g0(m + 1),g1(m + 1),h0(m + 1),h1(m + 1);

    for(int i = 1;i <= m;i++){
        ll x = n / i; // long long !!!
        g0[i] = Z(i) * (i + 1) / 2 - 1;
        g1[i] = Z(x) * (x + 1) / 2 - 1;
        h0[i] = Z(i) - 1;
        h1[i] = Z(x) - 1;
    }

    for(auto p : prime){
        ll pp = 1ll * p * p;
        Z gp = p;
        Z hp = 1;
        if(pp > n)break;
        //update 1
        for(int j = 1;j <= m && j * pp <= n;j++){
            g1[j] += gp * g0[p - 1];
            h1[j] += hp * h0[p - 1];
            if(1ll * p * j <= m){
                g1[j] -= gp * g1[p * j];
                h1[j] -= hp * h1[p * j];
            }
            else{
                g1[j] -= gp * g0[n / p / j];
                h1[j] -= hp * h0[n / p / j];
            } 
        }

        //update 0
        for(int j = m;j >= pp;j--){
            g0[j] -= gp * (g0[j / p] - g0[p - 1]);
            h0[j] -= hp * (h0[j / p] - h0[p - 1]);
        }
    }

    vector<Z>fprime0(m + 1),fprime1(m + 1);
    for(int i = 1;i <= m;i++){
        fprime0[i] = g0[i] - h0[i] + 2;
        fprime1[i] = g1[i] - h1[i] + 2;
    }
    fprime0[1] = 0;
    if(n == 1)fprime1[1] = 0; //！！！

    //calc f_0
    //F(n, k) = \sum_p \sum c f(p^c)F(n / p^c, k + 1) + f(p ^ (c + 1))

    auto F = [&](auto&&self, ll x, int k)->Z //F(n / x, k)
    {
        Z res = 0;
        if(k > 0)res -= fprime0[prime[k - 1]];
        if(x <= m)res += fprime1[x];
        else res += fprime0[n / x];

        for(int i = k, p = prime[i]; 1ll * p * p * x <= n;++i, p = prime[i]){
            ll pc = p;

            for(int c = 1; pc * p * x <= n;c++, pc *= p){
                res += Z(p ^ c) * self(self, x * pc, i + 1) + Z(p ^ (c + 1));
            }
        }
        return res;
    };

    return F(F, 1, 0) + 1;
}

void solve()
{
    ll n;
    cin>>n;
    cout<<min_25(n)<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}