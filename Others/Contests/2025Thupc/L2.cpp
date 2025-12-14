#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5 + 10, mod = 1e9 + 7;

ll n, q, a[N], s[N];
vector<ll> e[N], re[N];

ll qmi(ll a, ll k) {
    ll res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        k >>= 1;
        a = a * a % mod;
    }
    return res;
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) s[i] = (s[i - 1] + a[i]) % mod;
    for (int i = 1; i <= n; i++) {
        e[i].assign(n / i + 1, 0);
        ll inv = qmi(i, mod - 2);
        for (int j = 1; j < e[i].size(); j++) {
            int l = i * (j - 1) + 1, r = i * j;
            e[i][j] = (e[i][j - 1] + (s[r] - s[l - 1] + mod) % mod *
                                         (s[r] - s[l - 1] + mod) % mod * inv %
                                         mod * inv % mod) %
                      mod;
        }
    }

    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) s[i] = (s[i - 1] + a[i]) % mod;
    for (int i = 1; i <= n; i++) {
        re[i].assign(n / i + 1, 0);
        ll inv = qmi(i, mod - 2);
        for (int j = 1; j < re[i].size(); j++) {
            int l = i * (j - 1) + 1, r = i * j;
            re[i][j] = (re[i][j - 1] + (s[r] - s[l - 1] + mod) % mod *
                                           (s[r] - s[l - 1] + mod) % mod * inv %
                                           mod * inv % mod) %
                       mod;
        }
    }

    reverse(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) s[i] = (s[i - 1] + a[i]) % mod;

    while (q--) {
        int l, r;
        cin >> l >> r;
        int k = n / l, c = n - k * l;
        if (c) {
            if (k * (r - l) < c) {
                cout << "-1\n";
                continue;
            }
            int a = c / (r - l);
            ll res = e[r][a];
            c -= a * (r - l);
            int b = k - a;
            if (c) {
                b--;
                int x = a * r + 1;
                int y = l + x + c - 1;
                ll inv = qmi(l + c, mod - 2);
                res = (res + (s[y] - s[x - 1] + mod) % mod *
                                 (s[y] - s[x - 1] + mod) % mod * inv % mod *
                                 inv % mod) %
                      mod;
            }
            res = (res + re[l][b] + mod) % mod;
            cout << (res + mod) % mod << '\n';
        } else {
            cout << e[l][k] << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}