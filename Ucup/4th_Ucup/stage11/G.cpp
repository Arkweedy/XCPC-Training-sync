#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e6 + 10;
int n;
ll s[3][N];
array<ll, 3> a[N];
bool st[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) cin >> a[i][j];
    }

    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            s[j][i] = a[i][j] + s[j][i - 1];
        }
    }

    ll res = 0;
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i][0] >= p) {
            p = a[i][1];
            res += a[i][1] - a[i][0];
        } else {
            if (a[i][1] < p) {
                cout << -1 << '\n';
                return;
            }
            p = a[i][2];
            res += a[i][2] - a[i][1];
            st[i] = 1;
        }
    }

    for (int i = 1; i <= n;) {
        if (st[i]) continue;
        int ed = a[i][2];
        int j = i + 1;
        while (j <= n && !st[j] && ed > a[j][0]) {
            ed = a[j][2];
            j++;
        }

        if (j <= n && st[j] && ed > a[j][1]) {
            i = j;
            continue;
        }

        ll mx = 0;
        for (int k = i; k < j; k++) {
            ll val = a[k][2] - a[k][1] + s[2][j - 1] - s[2][k] + s[0][j - 1] -
                     s[0][k] - 2 * (s[1][j - 1] - s[1][k]);
            mx = max(mx, val);
        }

        res += mx;

        i = j;
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}