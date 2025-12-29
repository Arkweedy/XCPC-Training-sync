#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
 
const int P = 998244353;
const int mod = 998244353;

int qmi(ll a, ll k) {
    ll res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1;
        a = a * a % mod;
    }
    return res;
}

namespace NTT {
const int g = 3;
vector<int> Omega(int L) {
    int wn = qmi(g, mod / L);
    vector<int> w(L);
    w[L >> 1] = 1;
    for (int i = L / 2 + 1; i <= L - 1; i++) w[i] = 1ll * w[i - 1] * wn % mod;
    for (int i = L / 2 - 1; i; i--) w[i] = w[i << 1];
    return w;
}
auto W = Omega(1 << 21);  // NOLINT
void DIF(int* a, int n) {
    for (int k = n >> 1; k; k >>= 1)
        for (int i = 0, y; i < n; i += k << 1)
            for (int j = 0; j < k; j++)
                y = a[i + j + k],
                a[i + j + k] = 1ll * (a[i + j] - y + mod) * W[k + j] % mod,
                a[i + j] = (y + a[i + j]) % mod;
}
void IDIT(int* a, int n) {
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0, x, y; i < n; i += k << 1)
            for (int j = 0; j < k; j++)
                x = a[i + j], y = (1ll * a[i + j + k] * W[k + j]) % mod,
                a[i + j + k] = x - y < 0 ? x - y + mod : x - y,
                a[i + j] = (y + a[i + j]) % mod;
    int Inv = mod - (mod - 1) / n;
    for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * Inv % mod;
    reverse(a + 1, a + n);
}
// 用普通数组实现的NTT蝶形变化
}  // namespace NTT
namespace Polynomial {
using Poly = std::vector<int>;

// mul/div int
Poly& operator*=(Poly& a, int b) {
    for (auto& x : a) x = 1ll * x * b % mod;
    return a;
}
Poly operator*(Poly a, int b) { return a *= b; }
Poly operator*(int a, Poly b) { return b * a; }
Poly& operator/=(Poly& a, int b) { return a *= qmi(b, mod - 2); }
Poly operator/(Poly a, int b) { return a /= b; }

// Poly add/sub
Poly& operator+=(Poly& a, Poly b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) a[i] = (a[i] + b[i]) % mod;
    return a;
}
Poly operator+(Poly a, Poly b) { return a += b; }
Poly& operator-=(Poly& a, Poly b) {
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); i++) a[i] = (a[i] - b[i] + mod) % mod;
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
    for (int i = 0; i < a.size(); i++) a[i] = 1ll * a[i] * b[i] % mod;
    return a;
}
Poly operator*(Poly a, Poly b) {
    int n = a.size() + b.size() - 1, L = norm(n);
    if (a.size() <= 8 || b.size() <= 8) {
        Poly c(n);
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b.size(); j++)
                c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % mod;
        return c;
    }
    a.resize(L), b.resize(L);
    DFT(a), DFT(b), dot(a, b), IDFT(a);
    return a.resize(n), a;
}

// Poly inv 利用牛顿迭代递归实现的乘法逆
Poly Inv2k(Poly a) {  // a.size() = 2^k
    int n = a.size(), m = n >> 1;
    if (n == 1) return {qmi(a[0], mod - 2)};
    Poly b = Inv2k(Poly(a.begin(), a.begin() + m)), c = b;
    b.resize(n), DFT(a), DFT(b), dot(a, b), IDFT(a);
    for (int i = 0; i < n; i++) a[i] = i < m ? 0 : mod - a[i];
    DFT(a), dot(a, b), IDFT(a);
    return move(c.begin(), c.end(), a.begin()), a;
}
Poly Inv(Poly a) {
    int n = a.size();
    norm(a), a = Inv2k(a);
    return a.resize(n), a;
}

// Poly div/mod
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
    for (int i = 1; i < a.size(); i++) a[i - 1] = 1ll * i * a[i] % mod;
    return a.pop_back(), a;
}

// 此处如果预处理逆元的话大概可以优化
Poly integ(Poly a) {
    a.push_back(0);
    for (int i = a.size() - 1; i; i--)
        a[i] = 1ll * a[i - 1] * qmi(i, mod - 2) % mod;
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
            c[i] = a[i] - c[i] + (a[i] < c[i] ? mod : 0);
        c[0] = (c[0] + 1) % mod;
        DFT(b), DFT(c), dot(b, c), IDFT(b);
        move(d.begin(), d.end(), b.begin());
    }
    return b.resize(n), b;
}

Poly Pow(Poly& a, int b) { return Exp(Ln(a) * b); }  // a[0] = 1,多项式快速幂


}  // namespace Polynomial
using namespace Polynomial;

int Power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}


constexpr int N = 1e7 + 10;
int fac[N],invfac[N];

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    i64 s = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        s += a[i];
    }

    
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[N] = Power(fac[N], P - 2);
    for(int i = N - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    i64 ans = 0;
    i64 cs = 1;
    for(int i = 0;i < n;i++){
        cs = cs * ((n + s - i) % P) % P;
    }
    cs = cs * invfac[n] % P;

    ans += cs;

    auto binom = [&](int n, int m)->int
    {
        if(n < m || m < 0 || n < 0)return 0;
        return 1ll * fac[n] * invfac[n - m] % P * invfac[m] % P;
    };

    i64 res1 = 0;
    for(int i = 0;i < n;i++){
        if(s - i <= n * (n - i - 1)){
            //cerr << "in, i = " << i << endl;
            int k = (s - i) / (n - i);
            i64 ss = 0;
            //cerr << k << endl;
            for(int j = 0;j <= k;j++){
                i64 x = (j % 2 == 0 ? 1 : P-1);
                x = x * binom(n, j) % P;
                x = x * binom(n + s - i - j * (n - i) - 1, n - 1) % P;
                ss = (ss + x + P) % P;
                //cerr << x << endl;
            }
            //cerr << ss << endl;
            res1 += ss;
        }
    }
    ans -= res1;
    ans = (ans % P + P) % P;

    //cerr << ans << endl;
//    cout<<ans<<endl;
    int ill = 1;
    for(int i = 0;i < n;i++){
        if(a[i] >= n){
            ill = 0;
        }
    }
    vector<Poly> pre(n,Poly(n));
    auto  qp=[&](Poly a,int b)->Poly
    {
        Poly ans={1};
        while(b)
        {
            if(b&1) ans=ans*a,ans.resize(n);
            a=a*a;a.resize(n);b>>=1;
        }
        return ans;
    };
    if(ill){
        
        sort(a.begin(),a.begin()+n);

        for(int i=0;i<n;i++)
            for(int j=0;j<=a[i];j++) pre[i][j]=1;

        for(int i=1;i<n;i++) pre[i]=pre[i]*pre[i-1],pre[i].resize(n);

        int p=n-1;
        for(int k=0;k<n;k++)
        {
            while(p>=0&&a[p]>n-k-1)  p--;
            int u=0;
            for(int j=0;j<n;j++) u+=max(0,a[j]-(n-k-1));
            if(u>k) break;
            if(p<0) break;
            Poly g(n);
            for(int j=0;j<n-k;j++) g[j]=1;
        //    cout<<k<<' '<<p<<endl;
            //g=qp(g,n-p-1);
            g = qp(g,n-p-1);
            g = g * pre[p];
        //    cout<<u<<endl;
        //    cout<<pre[p][k-u]<<endl;
            ans=(ans+g[k-u])%P;

        }


    }
    ans = (ans % P + P) % P;
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