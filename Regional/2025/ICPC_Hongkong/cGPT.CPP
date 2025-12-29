#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

static constexpr int P = 998244353;

static inline int addmod(int a, int b){ a += b; if(a >= P) a -= P; return a; }
static inline int submod(int a, int b){ a -= b; if(a < 0) a += P; return a; }
static inline int mulmod(i64 a, i64 b){ return int(a * b % P); }

static int mod_pow(int a, i64 e){
    i64 r = 1, x = a;
    while(e){
        if(e & 1) r = r * x % P;
        x = x * x % P;
        e >>= 1;
    }
    return (int)r;
}

void solve(){
    int n;
    cin >> n;
    vector<int>a(n);
    i64 s = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        s += a[i];
    }

    // ========= 你原来的“组合数大段”基本照搬，只把 N=1e7 改成精确上界 need = n+s =========
    int need = 1e7;
    vector<int>fac(need + 1), invfac(need + 1);
    fac[0] = 1;
    for(int i = 1;i <= need;i++) fac[i] = mulmod(fac[i - 1], i);
    invfac[need] = mod_pow(fac[need], P - 2);
    for(int i = need;i >= 1;i--) invfac[i - 1] = mulmod(invfac[i], i);

    auto binom = [&](i64 N, i64 K)->int
    {
        if(N < 0 || K < 0 || K > N) return 0;
        if(N > need) return 0; // 正常不会发生
        int nN = (int)N, nK = (int)K;
        return mulmod(fac[nN], mulmod(invfac[nK], invfac[nN - nK]));
    };

    int ans = 0;
    i64 cs = 1;
    for(int i = 0;i < n;i++){
        cs = cs * ((n + s - i) % P) % P;
    }
    cs = cs * invfac[n] % P;

    ans += cs;

    int res1 = 0;
    for(int i = 0;i < n;i++){
        if(s - i <= 1LL * n * (n - i - 1)){
            int k = (int)((s - i) / (n - i));
            int ss = 0;
            for(int j = 0;j <= k;j++){
                int x = (j & 1) ? (P - 1) : 1;
                x = mulmod(x, binom(n, j));
                i64 top = (i64)n + s - i - 1 - 1LL * j * (n - i);
                x = mulmod(x, binom(top, n - 1));
                ss = addmod(ss, x);
            }
            res1 = addmod(res1, ss);
        }
    }
    ans = submod(ans, res1);

    // ========= 优化后的 ill 分支 =========
    bool ill = true;
    for(int v : a) if(v >= n){ ill = false; break; }

    if(ill){
        const int D = n - 1;   // 只需要到 n-1 次
        vector<int> f(D + 1), g(D + 1), ps(D + 1);
        f[0] = 1;

        // 乘 S_k(x)=1+x+...+x^k（截断到 D），O(D) 前缀和
        auto mul_S = [&](int k){
            ps[0] = f[0];
            for(int i = 1;i <= D;i++) ps[i] = addmod(ps[i - 1], f[i]);
            for(int t = 0;t <= D;t++){
                int val = ps[t];
                int l = t - k - 1;
                if(l >= 0) val = submod(val, ps[l]);
                g[t] = val;
            }
            f.swap(g);
        };

        // 初始 f = ∏ (1+...+x^{a_i})
        for(int v : a) mul_S(v);

        // cnt[v], ge[t] = #{a_i >= t}
        vector<int> cnt(n, 0), ge(n + 2, 0);
        for(int v : a) cnt[v]++;
        for(int t = n - 1;t >= 1;t--) ge[t] = ge[t + 1] + cnt[t];

        // inv[1..D] 供组合递推用
        vector<int> inv(D + 1);
        if(D >= 1){
            inv[1] = 1;
            for(int i = 2;i <= D;i++) inv[i] = mulmod(P - P / i, inv[P % i]);
        }

        // f *= Σ coef[p] * x^{p*step} （稀疏卷积，O(D * #terms)）
        auto mul_sparse = [&](const vector<int>& poly, int step, const vector<int>& coef){
            vector<int> res(D + 1, 0);
            for(int p = 0;p < (int)coef.size();p++){
                int c = coef[p];
                if(!c) continue;
                int sh = p * step;
                for(int d = sh;d <= D;d++){
                    res[d] = addmod(res[d], mulmod(c, poly[d - sh]));
                }
            }
            return res;
        };

        // f *= (1 - x^k)^c，系数：(-1)^p * C(c,p) * x^{pk}
        auto apply_pow_1minus = [&](int k, int c){
            if(c == 0) return;
            int L = min(D / k, c);
            vector<int> coef(L + 1);
            coef[0] = 1;
            i64 cur = 1; // C(c,p)
            for(int p = 1;p <= L;p++){
                cur = cur * (c - p + 1) % P * inv[p] % P;
                int v = (int)cur;
                coef[p] = (p & 1) ? (P - v) : v;
            }
            f = mul_sparse(f, k, coef);
        };

        // f *= (1 - x^k)^(-c)，系数：C(c+p-1,p) * x^{pk}
        auto apply_inv_pow_1minus = [&](int k, int c){
            if(c == 0) return;
            int L = D / k;
            vector<int> coef(L + 1);
            coef[0] = 1;
            i64 cur = 1; // C(c+p-1,p)
            for(int p = 1;p <= L;p++){
                cur = cur * (c + p - 1) % P * inv[p] % P;
                coef[p] = (int)cur;
            }
            f = mul_sparse(f, k, coef);
        };

        i64 use = 0;
        for(int i = 0;i < n;i++){
            if(use <= i){
                int idx = (int)(i - use);
                ans = addmod(ans, f[idx]);
            }else break;

            int cap = n - 1 - i; // 当前 cap
            if(cap == 0) break;

            int c = ge[cap];     // 需要把 S_cap -> S_{cap-1} 的个数
            use += c;

            // f *= ((1-x^cap)/(1-x^{cap+1}))^c
            apply_pow_1minus(cap, c);
            apply_inv_pow_1minus(cap + 1, c);
        }
    }

    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    // cin >> tt;
    while(tt--) solve();
    return 0;
}
