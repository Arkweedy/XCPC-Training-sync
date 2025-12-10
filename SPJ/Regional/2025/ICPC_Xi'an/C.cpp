#include <bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> d(n), nd(n), st(n);
    vector<vector<int>> e(n);

    while (m--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        e[u].push_back(v);
        e[v].push_back(u);
    }

    set<int> s;
    vector<int> f(n);
    int l = 0, r = 0;

    auto nadd = [&](int u) -> void {
        // 新图
        st[u] = 1;
        for (auto v : e[u]) {
            if (v < l || v >= r) continue;
            if (st[u] && st[v]) {
                nd[u]++, nd[v]++;
                if (nd[u] > 2) {
                    s.insert(u);
                }
                if (nd[v] > 2) {
                    s.insert(v);
                }
            }
        }
    };

    auto add = [&](int u) -> void {
        // 加入一个点到旧图
        for (auto v : e[u]) {
            if (v < l || v >= r) continue;
            d[u]++;
            d[v]++;
            if (d[v] == 2) {
                nadd(v);
            }
        }
        if (d[u] > 1) nadd(u);
    };

    auto ndel = [&](int u) -> void {
        for (auto v : e[u]) {
            if (v <= l || v > r) continue;
            if (st[u] && st[v]) {
                nd[u]--, nd[v]--;
                if (nd[u] <= 2) {
                    s.erase(u);
                }
                if (nd[v] <= 2) {
                    s.erase(v);
                }
            }
        }
        st[u] = 0;
    };

    auto del = [&](int u) -> void {
        ndel(u);
        for (auto v : e[u]) {
            if (v <= l || v > r) continue;
            d[u]--;
            d[v]--;
            if (d[v] == 1) {
                ndel(v);
            }
        }
    };

    //[l,r)
    for (l = 0; l < n; l++) {
        f[l] = r - 1;
        while (s.empty() && r < n) {
            f[l] = r;
            add(r);
            r++;
        }
        del(l);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (r > f[l])
            cout << "No\n";
        else
            cout << "Yes\n";
    }

    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while (tt--) {
        solve();
    }
    return 0;
}