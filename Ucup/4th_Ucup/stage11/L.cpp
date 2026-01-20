#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    if (a[0] == 1) {
        cout << "Bob\n";
        return;
    }
    if (n >= 2 && a[0] == 2 && a[1] == 2) {
        cout << "Bob\n";
        return;
    }
    if (k >= 4) {
        cout << "Ana\n";
        return;
    }
    if (k == 3) {

        if (a.back() >= 7) {
            cout << "Ana\n";
            return;
        }

        vector<int> cnt(10);
        for (auto x : a) cnt[x]++;

        if (cnt[6] >= 2) {
            cout << "Ana\n";
            return;
        }

        if (cnt[2] == 0) {
            if (cnt[3] || cnt[6])
                cout << "Ana\n";
            else {
                if (cnt[5] & 1)
                    cout << "Ana\n";
                else
                    cout << "Bob\n";
            }
        } else {
            //cnt[5] += cnt[6];
            if (cnt[5] % 2 == 0)
                cout << "Ana\n";
            else
                cout << "Bob\n";
        }

        return;
    }

    if (k == 2) {
        int cnt = 0;
        for (auto x : a) {
            if (x % 3 == 1) {
                cout << "Bob\n";
                return;
            }
            if (x % 3 == 2) {
                cnt++;
            }
        }
        if (cnt == 1)
            cout << "Ana\n";
        else
            cout << "Bob\n";
        return;
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}