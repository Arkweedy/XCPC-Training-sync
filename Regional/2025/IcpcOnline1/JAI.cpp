#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int MOD = 998244353;

int addmod(int a, int b){ int s = a + b; if(s >= MOD) s -= MOD; return s; }
int submod(int a, int b){ int s = a - b; if(s < 0) s += MOD; return s; }
int64 qpow(int64 a, int64 e){
    int64 r = 1;
    while(e){
        if(e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// floor/ceil for possibly negative numerator, positive denominator
long long floordiv2(long long a, long long b){ // b > 0
    if (a >= 0) return a / b;
    else return - ((-a + b - 1) / b);
}
long long ceildiv2(long long a, long long b){ // b > 0
    return - floordiv2(-a, b);
}

struct Solver1D {
    int N;
    long long M;
    int K;
    vector<long long> a;    // starting positions in 1D (u or v)

    vector<int> C;          // C(M, t)
    vector<int> pref;       // prefix sums of C

    Solver1D(int N_, long long M_, int K_, const vector<long long>& a_)
        : N(N_), M(M_), K(K_), a(a_) {
        // Precompute comb and prefix
        C.assign(M + 1, 0);
        vector<int> fact(M + 1), ifact(M + 1);
        fact[0] = 1;
        for(int i = 1; i <= M; ++i) fact[i] = (int64)fact[i-1] * i % MOD;
        ifact[M] = qpow(fact[M], MOD - 2);
        for(int i = M; i >= 1; --i) ifact[i-1] = (int64)ifact[i] * i % MOD;

        for(int t = 0; t <= M; ++t){
            C[t] = (int)((int64)fact[M] * ifact[t] % MOD * ifact[M - t] % MOD);
        }
        pref.assign(M + 1, 0);
        int run = 0;
        for(int t = 0; t <= M; ++t){
            run = addmod(run, C[t]);
            pref[t] = run;
        }
    }

    // sum of ways from a -> any p in [L, R]
    int waysum(long long ai, long long L, long long R){
        long long lo = ceildiv2(M + L - ai, 2);   // smallest t
        long long hi = floordiv2(M + R - ai, 2);  // largest t
        if (hi < 0 || lo > (long long)M || lo > hi) return 0;
        int Lt = (int)max(0LL, lo);
        int Rt = (int)min((long long)M, hi);
        if (Lt > Rt) return 0;
        int res = pref[Rt];
        if (Lt > 0) res = submod(res, pref[Lt - 1]);
        return res;
    }

    int solve(){
        long long minA = (long long)4e18, maxA = (long long)-4e18;
        for(long long x : a){ minA = min(minA, x); maxA = max(maxA, x); }
        long long tL = minA - M - K;   // ensure coverage for min partition
        long long tR = maxA + M;

        int ans = 0;
        for(long long t = tL; t <= tR; ++t){
            int prodA = 1, prodB = 1;
            long long L1 = t, R1 = t + K;
            long long L2 = t + 1, R2 = t + K;

            for(int i = 0; i < N; ++i){
                int s1 = waysum(a[i], L1, R1);
                int s2 = waysum(a[i], L2, R2);
                prodA = (int)((int64)prodA * s1 % MOD);
                prodB = (int)((int64)prodB * s2 % MOD);
                if (prodA == 0 && prodB == 0) break; // small pruning
            }
            ans = addmod(ans, submod(prodA, prodB));
        }
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; long long M; int K;
    if(!(cin >> N >> M >> K)) return 0;
    vector<long long> x(N), y(N);
    for(int i = 0; i < N; ++i) cin >> x[i] >> y[i];

    // u = x + y, v = x - y
    vector<long long> u(N), v(N);
    for(int i = 0; i < N; ++i){
        u[i] = x[i] + y[i];
        v[i] = x[i] - y[i];
    }

    Solver1D su(N, M, K, u);
    Solver1D sv(N, M, K, v);
    int Fu = su.solve();
    int Fv = sv.solve();
    cout << (int)((int64)Fu * Fv % MOD) << "\n";
    return 0;
}
