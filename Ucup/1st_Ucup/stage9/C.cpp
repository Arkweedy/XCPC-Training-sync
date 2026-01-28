#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vector<int> c;
    for (int i = 0; i < n;) {
        if (s[i] == t[i]) {
            i++;
            continue;
        }
        int j = i;
        while (j < n && s[j] != t[j]) j++;
        c.push_back(j - i);
        i = j;
    }
    if (c.size() > 2)
        cout << 0 << '\n';
    else if (c.size() == 2) {
        cout << 6 << '\n';
    } else if (c.size() == 1) {
        int x = c[0];
        //ll res = 1ll * n * n / 2 - 1ll * (x - 2) * (x - 2) / 2 - 1ll * (n - x) * (n - x) / 2;
        cout << res << '\n';
    } else {
        cout << 1ll * n * (n + 1) / 2 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}