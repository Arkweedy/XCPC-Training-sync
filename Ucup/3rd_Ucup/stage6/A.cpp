#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937_64 rng(
    std::chrono::steady_clock::now().time_since_epoch().count());

/*
9 6

s 是 奇数 x 是 偶数



*/

ll range(ll l, ll r) {
    ll len = r - l + 1;
    return rng() % len + l;
}

constexpr int inf = 1e9 - 1;

void solve() {
    ll s, t;
    cin >> s >> t;
    if (gcd(s, t) == 1) {
        cout << 1 << '\n' << s << '\n';
    } 
    else if (s % 2 && t % 2 == 0) {
        ll l = -inf, r = inf;
        while (1) {
            ll x = range(l, r);
            ll y = range(l, r);
            ll z = s - x - y;
            if (z >= l && z <= r && gcd(t, abs(x)) == 1 &&
                gcd(t, abs(y)) == 1 && gcd(t, abs(z)) == 1) {
                cout << "3\n";
                cout << x << ' ' << y << ' ' << z << '\n';
                break;
            }
        }
    } 
    else {
        ll l = -inf, r = inf;
        while (1) {
            ll x = range(l, r);
            ll z = s - x;
            if (z >= l && z <= r && gcd(t, abs(x)) == 1 &&
                gcd(t, abs(z)) == 1) {
                cout << "2\n";
                cout << x << ' ' << z << '\n';
                break;
            }
        }
    }
    vector<int>a;
    a.shrink_to_fit();
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}