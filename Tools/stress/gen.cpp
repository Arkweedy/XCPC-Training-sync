#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());

    auto rnd = [&](int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng);
    };

    int T = 1;
    cout << T << '\n';

    int n = rnd(2, 18);
    int q = rnd(1, 35);
    cout << n << ' ' << q << '\n';

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int mode = rnd(0, 99);
        int val;
        if (mode < 35) {
            val = 0;
        } else if (mode < 70) {
            val = 1 << rnd(0, 5);
        } else {
            val = rnd(0, 63);
        }
        a[i] = val;
    }

    vector<pair<int, int>> edges;
    for (int v = 2; v <= n; v++) {
        int u = rnd(1, v - 1);
        edges.push_back({u, v});
    }

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    shuffle(p.begin() + 1, p.end(), rng);

    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) {
        b[p[i]] = a[i];
    }
    for (int i = 1; i <= n; i++) {
        cout << b[i] << " \n"[i == n];
    }

    for (auto [u, v] : edges) {
        cout << p[u] << ' ' << p[v] << '\n';
    }

    for (int i = 0; i < q; i++) {
        int u = rnd(1, n);
        int v = rnd(1, n - 1);
        if (v >= u) {
            v++;
        }
        cout << u << ' ' << v << '\n';
    }

    return 0;
}
