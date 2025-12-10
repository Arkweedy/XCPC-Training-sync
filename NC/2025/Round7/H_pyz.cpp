#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5 + 10;

int n, a[N], p[N], lp[N], rp[N];
int pr[N], pl[N], tot;
ll s1[N], s2[N], s3[N], res;
// 按照值域区间均摊。

//calc prefix of suffix
//345->3,34,345

void get(int l, int r) {
    if (l == r) {
        int x = p[l];
        res += 1ll * (rp[x] - x) * (x - lp[x]);
        // cout << l << ' ' << r << ' ' << res << endl;
        return;
    }
    int mid = l + r >> 1;

    get(l, mid), get(mid + 1, r);
    tot = 0;
    for (int i = mid + 1; i <= r; i++) {
        ++tot;
        pr[tot] = pl[tot] = p[i];
        pr[tot] = max(pr[tot], pr[tot - 1]);
        pl[tot] = min(pl[tot], pl[tot - 1]);
    }
    int la = n + 1, ra = 0;
    for (int i = mid; i >= l; i--) {
        int x = p[i];
        la = min(la, p[i]);
        ra = max(ra, p[i]);
        if (la < lp[x] || ra > rp[x]) continue;
        for (int j = mid + 1; j <= r; j++) {
            if (p[j] > rp[x] || p[j] < lp[x]) break;
            res += 1ll * (rp[x] - max(ra, pr[j - mid])) *
                   (min(la, pl[j - mid]) - lp[x]);
        }
    }
    // cout << l << ' ' << r << ' ' << res << endl;
}

void solve() {
    cin >> n;
    res = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], p[a[i]] = i;

    pl[0] = n + 1, pr[0] = 0;
    a[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        int j = i - 1;
        while (a[j] > a[i]) j = lp[j];
        lp[i] = j;//first lower
    }
    ll sum = 0;
    for (int i = n; i; i--) {
        int j = i + 1;
        while (a[j] > a[i]) j = rp[j];
        rp[i] = j;//first greater
        sum += 1ll * a[i] * (rp[i] - i) * (i - lp[i]);
        // cout << a[i] << ' ' << lp[i] << ' ' << rp[i] << endl;
    }
    // cout << sum << '\n';
    get(1, n);
    cout << res + sum << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}