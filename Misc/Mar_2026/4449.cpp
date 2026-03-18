#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//4449.cpp Create time : 2026.03.18 16:00

constexpr int MOD = 1'000'000'007;

int qpow(int a, int b)
{
    int res = 1;
    while (b) {
        if (b & 1) {
            res = 1LL * res * a % MOD;
        }
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T, k;
    cin >> T >> k;

    vector<pair<int, int>> ask(T);
    int lim = 0;
    for (auto &[n, m] : ask) {
        cin >> n >> m;
        if (n > m) {
            swap(n, m);
        }
        lim = max(lim, n);
    }

    vector<int> prime;
    vector<bool> isprime(lim + 1, true);
    vector<int> pw(lim + 1), val(lim + 1), pre(lim + 1);

    if (lim >= 0) {
        isprime[0] = false;
    }
    if (lim >= 1) {
        isprime[1] = false;
        pw[1] = 1;
        val[1] = 1;
    }

    for (int i = 2; i <= lim; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            pw[i] = qpow(i, k);
            val[i] = pw[i] - 1;
        }
        for (auto &p : prime) {
            if (1LL * p * i > lim) {
                break;
            }
            isprime[i * p] = false;
            pw[i * p] = 1LL * pw[i] * pw[p] % MOD;
            if (i % p == 0) {
                val[i * p] = 1LL * val[i] * pw[p] % MOD;
                break;
            }
            else {
                val[i * p] = 1LL * val[i] * val[p] % MOD;
            }
        }
    }

    for (int i = 1; i <= lim; i++) {
        pre[i] = pre[i - 1] + val[i];
        if (pre[i] >= MOD) {
            pre[i] -= MOD;
        }
    }

    for (auto &[n, m] : ask) {
        int ans = 0;
        for (int l = 1, r; l <= n; l = r + 1) {
            int dn = n / l;
            int dm = m / l;
            r = min(n / dn, m / dm);
            int seg = pre[r] - pre[l - 1];
            if (seg < 0) {
                seg += MOD;
            }
            ans = (ans + 1LL * seg * dn % MOD * dm) % MOD;
        }
        cout << ans << '\n';
    }

    return 0;
}
