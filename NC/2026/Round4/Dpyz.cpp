#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int n = 6;
// op = 0 min  op = 1 max
vector<int> dfs(vector<int> cur, int mask, int op) {
    if (mask + 1 == (1 << n)) {
        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (cur[i] == 0) {
                for (int j = 0; j < n; j++) res.push_back(cur[(i + j) % n]);
                break;
            }
        }
        return res;
    }

    vector<int> res(n);
    if (op) {
        fill(res.begin(), res.end(), 0);
    } else {
        fill(res.begin(), res.end(), n);
    }

    for (int i = 0; i < n; i++) {
        if (mask >> i & 1) continue;
        cur.push_back(i);
        if (op) {
            res = max(res, dfs(cur, mask | (1 << i), op ^ 1));
        } else {
            res = min(res, dfs(cur, mask | (1 << i), op ^ 1));
        }
        cur.pop_back();
    }

    return res;
}

void solve() {
    cin >> n;
    vector<int> ans;

    if (n == 1) {
        ans.push_back(1);
    } else if (n % 2 == 0) {
        // n = 2m
        int m = n / 2;
        ans.push_back(1);
        ans.push_back(m + 1);
        for (int i = 0; i <= m - 2; i++) {
            ans.push_back(m - i);
            ans.push_back(m + 2 + i);
        }
    } else {
        // n = 2m + 1
        int m = n / 2;
        ans.push_back(1);
        ans.push_back(m + 2);
        ans.push_back(2);
        for (int i = 0; i <= m - 2; i++) {
            ans.push_back(m + 1 - i);
            ans.push_back(m + 3 + i);
        }
    }

    for (auto x : ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}