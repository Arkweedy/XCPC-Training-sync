#include <bits/stdc++.h>
using namespace std;

/* ========== 参数区 ========== */
const int T     = 10;
const int MAX_N = 1'000;
const int MAX_M = 1'000;
const int MAX_C = 10;
/* =========================== */

mt19937 g(chrono::steady_clock::now().time_since_epoch().count());

int rand_int(int l, int r) {
    return uniform_int_distribution<int>(l, r)(g);
}

void gen_case(bool infinite = false, bool no_solution = false, bool all_same = false) {
    int n = rand_int(1, MAX_N);
    int m = MAX_M;
    int c;

    if (infinite) {
        c = 1;
        n = (n / c) * c;
        cout << n << ' ' << m << ' ' << c << '\n';
        int val = rand_int(0, m);
        for (int i = 0; i < n; ++i) cout << val << " \n"[i == n - 1];
        return;
    }

    if (no_solution) {
        c = rand_int(2, min(n, MAX_C));
        n = (n / c) * c;
        cout << n << ' ' << m << ' ' << c << '\n';
        int val = rand_int(0, m);
        for (int i = 0; i < n; ++i) cout << val << " \n"[i == n - 1];
        return;
    }

    if (all_same) {
        c = 1;
        n = (n / c) * c;
        cout << n << ' ' << m << ' ' << c << '\n';
        for (int i = 0; i < n; ++i) cout << rand_int(0, m) << " \n"[i == n - 1];
        return;
    }

    c = rand_int(1, min(n, MAX_C));
    n = (n / c) * c;
    cout << n << ' ' << m << ' ' << c << '\n';

    //set<int> vals;
    //while ((int)vals.size() < c) vals.insert(rand_int(0, m));

    vector<int> res;
    //for (int v : vals)
        for (int i = 0; i < n; ++i) res.push_back(rand_int(0, m));

    shuffle(res.begin(), res.end(), g);
    for (int i = 0; i < n; ++i) cout << res[i] << " \n"[i == n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << T << '\n';

    // 生成一些边界情况
    gen_case(true);           // 无限解
    gen_case(false, true);    // 无解
    gen_case(false, false, true); // 所有数相同，c=1

    for (int i = 0; i < T - 3; ++i) gen_case();

    return 0;
}