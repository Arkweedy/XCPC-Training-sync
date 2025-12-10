#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e6 + 10, INF = 1e9;
struct info {
    int a, b;
} x[N];
int n, p[N];
void solve() {
    // cin >> n;
    n = 500;
    for (int i = 1; i <= n; i++) {
        // cin >> x[i].a >> x[i].b;
        x[i].a = rng() % INF + 1;
        x[i].b = rng() % INF + 1;
    }
    sort(x + 1, x + n + 1, [](info x, info y) { return x.b < y.b; });
    for (int i = 1; i <= n; i++) {
        ll ans = 1e18;
        int t = 0;
        for (int j = i; j <= n; j++) {
            vector<int> c;
            ll sum = x[j].b;
            for (int k = 1; k <= j; k++) c.push_back(x[k].a);
            sort(c.begin(), c.end());
            for (int k = 0; k < i; k++) sum += c[k];
            if (sum < ans) ans = sum, t = j;
        }
        p[i] = t;
        assert(p[i] >= p[i - 1]);
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}