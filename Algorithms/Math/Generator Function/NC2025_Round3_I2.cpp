#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 998244353;

int qmi(ll a, ll k) {
    ll res = 1;
    while (k) {
        if (k & 1) res = res * a % P;
        k >>= 1;
        a = a * a % P;
    }
    return res;
}

int inv(ll a) {
    return qmi(a, P - 2);
}

namespace NTT {
const int g = 3;
vector<int> Omega(int L) {
    int wn = qmi(g, P / L);
    vector<int> w(L);
    w[L >> 1] = 1;
    for (int i = L / 2 + 1; i <= L - 1; i++) w[i] = 1ll * w[i - 1] * wn % P;
    for (int i = L / 2 - 1; i; i--) w[i] = w[i << 1];
    return w;
}
auto W = Omega(1 << 21);  // NOLINT
void DIF(int* a, int n) {
    for (int k = n >> 1; k; k >>= 1)
        for (int i = 0, y; i < n; i += k << 1)
            for (int j = 0; j < k; j++)
                y = a[i + j + k],
                a[i + j + k] = 1ll * (a[i + j] - y + P) * W[k + j] % P,
                a[i + j] = (y + a[i + j]) % P;
}
void IDIT(int* a, int n) {
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0, x, y; i < n; i += k << 1)
            for (int j = 0; j < k; j++)
                x = a[i + j], y = (1ll * a[i + j + k] * W[k + j]) % P,
                a[i + j + k] = x - y < 0 ? x - y + P : x - y,
                a[i + j] = (y + a[i + j]) % P;
    int Inv = P - (P - 1) / n;
    for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * Inv % P;
    reverse(a + 1, a + n);
}
// 用普通数组实现的NTT蝶形变化
}  // namespace NTT
namespace Polynomial {
using Poly = std::vector<int>;

// mul/div int
Poly& operator*=(Poly& a, int b) {
    for (auto& x : a) x = 1ll * x * b % P;
    return a;
}
Poly operator*(Poly a, int b) { return a *= b; }
Poly operator*(int a, Poly b) { return b * a; }
Poly& operator/=(Poly& a, int b) { return a *= qmi(b, P - 2); }
Poly operator/(Poly a, int b) { return a /= b; }

// Poly add/sub
Poly& operator+=(Poly& a, Poly b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) a[i] = (a[i] + b[i]) % P;
    return a;
}
Poly operator+(Poly a, Poly b) { return a += b; }
Poly& operator-=(Poly& a, Poly b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) a[i] = (a[i] - b[i] + P) % P;
    return a;
}
Poly operator-(Poly a, Poly b) { return a -= b; }

// Poly mul
void DFT(Poly& a) { NTT::DIF(a.data(), a.size()); }
void IDFT(Poly& a) { NTT::IDIT(a.data(), a.size()); }
int norm(int n) {
    return 1 << (32 - __builtin_clz(n - 1));
}  // 返回大于等于n的最小2的整数次幂
void norm(Poly& a) {
    if (!a.empty()) a.resize(norm(a.size()), 0);
}  // 剩余的用0填
Poly& dot(Poly& a, Poly& b) {
    for (int i = 0; i < a.size(); i++) a[i] = 1ll * a[i] * b[i] % P;
    return a;
}
Poly operator*(Poly a, Poly b) {
    int n = a.size() + b.size() - 1, L = norm(n);
    if (a.size() <= 8 || b.size() <= 8) {
        Poly c(n);
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b.size(); j++)
                c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % P;
        return c;
    }
    a.resize(L), b.resize(L);
    DFT(a), DFT(b), dot(a, b), IDFT(a);
    return a.resize(n), a;
}

// Poly inv 利用牛顿迭代递归实现的乘法逆
Poly Inv2k(Poly a) {  // a.size() = 2^k
    int n = a.size(), m = n >> 1;
    if (n == 1) return {qmi(a[0], P - 2)};
    Poly b = Inv2k(Poly(a.begin(), a.begin() + m)), c = b;
    b.resize(n), DFT(a), DFT(b), dot(a, b), IDFT(a);
    for (int i = 0; i < n; i++) a[i] = i < m ? 0 : P - a[i];
    DFT(a), dot(a, b), IDFT(a);
    return move(c.begin(), c.end(), a.begin()), a;
}
Poly Inv(Poly a) {
    int n = a.size();
    norm(a), a = Inv2k(a);
    return a.resize(n), a;
}

// Poly div/P
Poly operator/(Poly a, Poly b) {
    int k = a.size() - b.size() + 1;
    if (k < 0) return {0};
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    b.resize(k), a = a * Inv(b);
    a.resize(k), reverse(a.begin(), a.end());
    return a;
}
pair<Poly, Poly> operator%(Poly a, const Poly& b) {
    Poly c = a / b;
    a -= b * c, a.resize(b.size() - 1);
    return {c, a};
}

// 求导和积分
Poly deriv(Poly a) {
    for (int i = 1; i < a.size(); i++) a[i - 1] = 1ll * i * a[i] % P;
    return a.pop_back(), a;
}

// 此处如果预处理逆元的话大概可以优化
Poly integ(Poly a) {
    a.push_back(0);
    for (int i = a.size() - 1; i; i--)
        a[i] = 1ll * a[i - 1] * qmi(i, P - 2) % P;
    return a[0] = 0, a;
}

// Poly 要求a[0] = 1
Poly Ln(Poly a) {
    int n = a.size();
    a = deriv(a) * Inv(a);
    return a.resize(n - 1), integ(a);
}

// Poly exp
Poly Exp(Poly a) {
    int n = a.size(), k = norm(n);
    Poly b = {1}, c, d;
    a.resize(k);
    for (int L = 2; L <= k; L <<= 1) {
        d = b, b.resize(L), c = Ln(b), c.resize(L);
        for (int i = 0; i < L; i++)
            c[i] = a[i] - c[i] + (a[i] < c[i] ? P : 0);
        c[0] = (c[0] + 1) % P;
        DFT(b), DFT(c), dot(b, c), IDFT(b);
        move(d.begin(), d.end(), b.begin());
    }
    return b.resize(n), b;
}

Poly Pow(Poly& a, int b) { return Exp(Ln(a) * b); }  // a[0] = 1,多项式快速幂

}  // namespace Polynomial
using namespace Polynomial;


void solve()
{
    int t, k;
    cin>>t>>k;
    constexpr int N = 2e5;
    Poly f(N + 1);
    vector<int> fac(N + 1);
    f[0] = fac[0] = 1;
    

    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
        f[i] = qmi(inv(fac[i]), k + 1);
    }

    auto g = Ln(f);

    Poly h(N + 1);
    //n log^2
    for(int i = 1;i <= N;i++){
        for(int j = 0;i * j <= N;j++){
            h[i * j] = (h[i * j] + 1ll * g[j] * qmi(inv(i),1ll * j * (k + 1))) % P;
        }
    }

    auto ans = Exp(h);
    
    for(int i = 1;i <= N;i++){
        ans[i] = 1ll * ans[i] * qmi(fac[i], k + 1) % P;
    }

    while(t--){
        int n;
        cin>>n;
        cout<<ans[n]<<"\n";
    }
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

// 1 1 748683265 859599304 552847133 581130723 598451726 52957968 749510733 
// 0 1 249561088 443664157 722687318 460856143 688642256 443428366 398439011 
// 0 1 0 887328314 675894614 780294336 896417267 137843360 51291576 

// 1 1 748683265 859599304 552847133 581130723 598451726 52957968 749510733 
// 0 1 249561088 443664157 722687318 460856143 688642256 443428366 398439011 
// 0 1 249561092 443664166 722687330 460856168 383623171 443428415 731187114 
