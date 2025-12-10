#include <bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr int mod = 998244353;

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
constexpr int g = 3;
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
}  
void norm(Poly& a) {
    if (!a.empty()) a.resize(norm(a.size()), 0);
}  
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

// Poly inv by Newton method
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


Poly deriv(Poly a) {
    for (int i = 1; i < a.size(); i++) a[i - 1] = 1ll * i * a[i] % mod;
    return a.pop_back(), a;
}


Poly integ(Poly a) {
    a.push_back(0);
    for (int i = a.size() - 1; i; i--)
        a[i] = 1ll * a[i - 1] * qmi(i, mod - 2) % mod;
    return a[0] = 0, a;
}


Poly Ln(Poly a) {
    int n = a.size();
    a = deriv(a) * Inv(a);
    return a.resize(n - 1), integ(a);
}


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

Poly Pow(Poly& a, int b) { return Exp(Ln(a) * b); }  

}
using namespace Polynomial;



// 定义全局常量和数组
constexpr int MAXN = 200005;

ll fact[MAXN];
ll invFact[MAXN];
int final_ans[MAXN];  // 最终答案数组

void pre_calc(int N, ll k) {
    //
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fact[i] = (fact[i - 1] * i) % mod;
        invFact[i] = qmi(fact[i], mod - 2);
    }

    ll K = k + 1;//k + 1 -> |v|^k , |v| times

    // calc D(x) = Ln(B(x))
    // D(x) = sum_{j=1}^N ln(C_j(x))
    Poly d(N + 1, 0);

    for (int j = 1; j <= N; ++j) {
        int limit = N / j;
        if (limit == 0) continue;

        // 构造多项式 P_j(y) = sum_{m=0 to limit} y^m / ((j^m * m!)^K)
        Poly Pj(limit + 1);
        ll invj = qmi(j, mod - 2);
        ll inv_j_pow_K = qmi(invj, K);
        ll current_inv_j_K_pow_m = 1;  // 迭代计算 (inv_j^K)^m

        for (int m = 0; m <= limit; ++m) {
            ll term1 = qmi(invFact[m], K);
            Pj[m] = (int)((term1 * current_inv_j_K_pow_m) % mod);
            current_inv_j_K_pow_m = (current_inv_j_K_pow_m * inv_j_pow_K) % mod;
        }

        // P_j[0] 必须为 1 才能进行对数运算，我们的构造满足此条件

        // 计算 ln(P_j(y))
        Poly Lj = Ln(Pj);

        // 将 ln(P_j(y)) 的系数贡献到 d_n 上
        // d_n = sum_{j|n} [y^{n/j}] ln(P_j(y))
        for (int t = 1; t <= limit; ++t) {
            if (t < Lj.size()) {
                d[j * t] = (d[j * t] + Lj[t]) % mod;
            }
        }
    }

    // 3. 计算 B(x) = exp(D(x))
    // d[0] 必须为 0 才能进行指数运算，我们的构造满足此条件
    Poly B = Exp(d);

    // 4. 计算所有 n 的最终答案 A_n = (n!)^K * B_n
    final_ans[0] = 1;  // 题目 n>=1，但按定义 A_0=1
    for (int n = 1; n <= N; ++n) {
        ll n_fact_pow_K = qmi(fact[n], K);
        if (n < B.size()) {
            final_ans[n] = (int)((n_fact_pow_K * B[n]) % mod);
        } else {
            // 正常情况下 B 的大小会等于 N+1，不会进入此分支
            final_ans[n] = 0;
        }
    }
}

void solve()
{
    int t;
    ll k;
    cin >> t >> k;

    // 为了确定预计算的范围，先读取所有查询
    vector<int> qry(t);
    int ma = 0;
    for (int i = 0; i < t; ++i) {
        cin >> qry[i];
        if (qry[i] > ma) {
            ma = qry[i];
        }
    }
    pre_calc(ma, k);
    
    for (auto n : qry) {
        cout << final_ans[n] << "\n";
    }

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}