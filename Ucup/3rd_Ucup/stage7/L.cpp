#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;
    int B = 2 * sqrt(n);
    vector<ll> a(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    ll res = 0;
    if (n <= 1000) {
        for (int i = 1; i <= n; i++) {
            ll val = 1ll * i * i;
            for (int j = i; j <= n; j++) {
                if (s[j] - s[j - i] == val) res++;
            }
        }
    } 
    else {
        // for (int i = 1; i <= B; i++) {
        //     ll val = 1ll * i * i;
        //     for (int j = i; j <= n; j++) {
        //         if (s[j] - s[j - i] == val) res++;
        //     }
        // }
        res++;
        int l = max(n / 2 - B, B + 1), r = n / 2 + B;
        for (int i = l; i <= r; i++) {
            ll val = 1ll * i * i;
            for (int j = i; j <= n; j++) {
                if (s[j] - s[j - i] == val) res++;
            }
        }
    }
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}