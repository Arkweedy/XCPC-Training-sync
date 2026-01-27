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
constexpr int P = 19260817;
//constexpr int P = 1000000007;
using Z = MInt<P>;

constexpr int N = 1000100;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;
vector<Z>fac;
vector<Z>f;
vector<Z>prodf;
vector<Z>invprodf;
vector<Z>inv;

void seive()
{
    isprime.set();
    mu.resize(N + 1);
    fac.resize(N + 1);
    f.resize(N + 1, 1);
    prodf.resize(N + 1, 1);
    invprodf.resize(N + 1, 1);
    inv.resize(N + 1);
    isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)
                break;
            isprime.flip(i * p);
            //mu
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            else {
                mu[i * p] = mu[i] * (-1);
            }
        }
    }

    fac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = fac[i - 1] * i;
        inv[i] = Z(i).inv();
    }

    for(int i = 1;i <= N;i++){
        for(int j = 1;j * i <= N;j++){
            if(mu[j] == 1)f[i * j] *= i;
            else if(mu[j] == -1)f[i * j] *= inv[i];
        }
    }
    for(int i = 1;i <= N;i++){
        prodf[i] = prodf[i - 1] * f[i];
        invprodf[i] = prodf[i].inv();
    }
}


//没想到还可以用\phi 来莫反
//之前见过也写过，但是有段时间没写给忘了
// \sum_{i = 1 \leq x} [gcd(i, x) == 1] = \phi(x)
//确实是合乎定义的

//也就是说 
//f(n) = \prod_{d | n} d^{\mu(n / d)}
//也应该可以用含 \phi 的式子表达出来？
//或许还是有些麻烦
//不过两种求法应该是都可以的


void solve()
{
    int n;
    cin>>n;
    
    auto calc1 = [&](int n)->Z
    {
        return power(fac[n], n * 2);
    };

    auto calc2 = [&](int n)->Z
    {
        Z res = 1;
        for(int l = 1, r;l <= n;l = r + 1){
            r = n / (n / l);
            res *= power(prodf[r] * invprodf[l - 1], 1ll * (n / l) * (n / l) % (P - 1));
        }
        return res * res;
    };

    Z ans = calc1(n) / calc2(n);
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}