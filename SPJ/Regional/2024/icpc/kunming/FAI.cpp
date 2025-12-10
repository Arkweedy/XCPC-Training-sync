#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using i64 = long long;
using u128 = __uint128_t;

// -------------------- fast pow mod --------------------
i64 mod_pow(i64 a, i64 e, i64 mod) {
    i64 r = 1 % mod;
    a %= mod;
    while (e) {
        if (e & 1) r = ( (__int128)r * a ) % mod;
        a = ( (__int128)a * a ) % mod;
        e >>= 1;
    }
    return r;
}

// -------------------- integer power check --------------------
bool pow_le(u64 a, int e, u64 n) {
    if (e == 0) return 1 <= n;
    u128 r = 1, A = a, N = n;
    for (int i = 0; i < e; ++i) {
        r *= A;
        if (r > N) return false;
    }
    return true;
}

// floor(n^{1/e}) using long double + adjust safely
u64 iroot(u64 n, int e) {
    if (e == 1) return n;
    long double x = pow((long double)n, 1.0L / e);
    u64 t = (u64)floor(x + 0.5L);
    if (t == 0) t = 1;
    while (!pow_le(t, e, n)) --t;
    while (pow_le(t + 1, e, n)) ++t;
    return t;
}

// -------------------- Sieve up to MAXS for Lehmer --------------------
const int MAXS = 5000000; // 5e6
vector<int> primes;
vector<int> pi_small(MAXS + 1);
bitset<MAXS + 1> is_comp;

void sieve() {
    is_comp.reset();
    is_comp[0] = is_comp[1] = 1;
    for (int i = 2; i * 1LL * i <= MAXS; ++i) {
        if (!is_comp[i]) {
            for (int j = i * i; j <= MAXS; j += i) is_comp[j] = 1;
        }
    }
    for (int i = 2; i <= MAXS; ++i) {
        if (!is_comp[i]) primes.push_back(i);
        pi_small[i] = pi_small[i - 1] + (!is_comp[i]);
    }
}

// -------------------- Lehmer prime counting pi(x) --------------------
unordered_map<u64, u64> phi_cache;
// key pack (x,s) into 128? We'll combine as (x<<7)|s since s small
inline u64 pack_key(u64 x, int s) { return (x << 7) ^ (u64)s; }

u64 phi(u64 x, int s) {
    if (s == 0) return x;
    if (s == 1) return x - x / 2;
    if (s == 2) return x - x / 2 - x / 3 + x / 6;
    if (s == 3) { // primes 2,3,5
        return x - x/2 - x/3 - x/5 + x/6 + x/10 + x/15 - x/30;
    }
    u64 key = pack_key(x, s);
    auto it = phi_cache.find(key);
    if (it != phi_cache.end()) return it->second;
    u64 res = phi(x, s - 1) - phi(x / primes[s - 1], s - 1);
    phi_cache.emplace(key, res);
    return res;
}

u64 pi_lehmer(u64 x); // forward

u64 PI(u64 x) {
    if (x <= (u64)MAXS) return pi_small[(int)x];
    return pi_lehmer(x);
}

// Lehmer π(x). Needs primes[] at least up to ~1e6; we have 5e6
u64 pi_lehmer(u64 x) {
    if (x <= (u64)MAXS) return pi_small[(int)x];
    long double sx = sqrtl((long double)x);
    long double cx = cbrtl((long double)x);
    long double qx = pow((long double)x, 0.25L);

    u64 a = PI((u64)qx);
    u64 b = PI((u64)sx);
    u64 c = PI((u64)cx);

    u64 sum = phi(x, (int)a) + (b + a - 2) * (b - a + 1) / 2;

    for (u64 i = a + 1; i <= b; ++i) {
        u64 p = primes[(size_t)i - 1];
        u64 w = x / p;
        sum -= PI(w);
        if (i <= c) {
            u64 bi = PI((u64)floor(sqrtl((long double)w)));
            for (u64 j = i; j <= bi; ++j) {
                u64 pj = primes[(size_t)j - 1];
                sum -= PI(w / pj) - (j - 1);
            }
        }
    }
    return sum;
}

// -------------------- counting N_k by recursion --------------------
u64 N_val_mod; // modulus p-1, to keep exponents small
vector<int> primes_enum; // primes up to sqrt(n) for enumeration

// count numbers <= limit with exactly k distinct prime factors, all >= lo
u64 count_k(u64 limit, int k, u64 lo) {
    if (k == 0) return 1; // exact picked set fits
    if (k == 1) {
        if (limit < lo) return 0;
        u64 res = 0;
        for (int e = 1;; ++e) {
            u64 t = iroot(limit, e);
            if (t < lo || t < 2) break;
            u64 add = PI(t) - PI(lo - 1);
            res = (res + (add % N_val_mod)) % N_val_mod;
        }
        return res;
    }
    u64 res = 0;
    // iterate primes p >= lo with p^k <= limit
    size_t idx = lower_bound(primes_enum.begin(), primes_enum.end(), (int)lo) - primes_enum.begin();
    for (size_t i = idx; i < primes_enum.size(); ++i) {
        u64 p = primes_enum[i];
        if (!pow_le(p, k, limit)) break;
        u64 t = limit;
        while (t >= p) {
            t /= p;
            u64 sub = count_k(t, k - 1, p + 1);
            res += sub;
            if (res >= N_val_mod) res -= N_val_mod;
        }
    }
    return res % N_val_mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    u64 n; i64 modp;
    if (!(cin >> n >> modp)) return 0;

    sieve();

    // primes for enumeration up to sqrt(n)
    u64 S = (u64)floor(sqrtl((long double)n));
    for (int p : primes) {
        if ((u64)p > S) break;
        primes_enum.push_back(p);
    }

    // exponent modulus
    N_val_mod = (u64)(modp - 1);

    i64 ans = 1 % modp;
    i64 all = 0;
    // k starts from 2 (k=1 contributes 1)
    for (int k = 2; ; ++k) {
        // quick stop: product of first k primes > n -> N_k = 0
        u128 prod = 1;
        for (int i = 0; i < k; ++i) {
            if (i >= (int)primes_enum.size()) { prod = (u128)n + 1; break; }
            prod *= (u128)primes_enum[i];
            if (prod > (u128)n) break;
        }
        if (prod > (u128)n) break;

        u64 Nk_mod = count_k(n, k, 2);
        all += Nk_mod;
        cerr<<Nk_mod<<endl;
        if (Nk_mod) {
            ans = ( (__int128)ans * mod_pow(k % modp, (i64)Nk_mod % (modp - 1), modp) ) % modp;
        }
    }
    cerr<<all<<endl;
    cout << ans % modp << '\n';
    return 0;
}
