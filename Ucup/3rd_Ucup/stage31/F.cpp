#include <bits/stdc++.h>

#define ln (p << 1)
#define rn (p << 1 | 1)
#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5 + 10, M = 2e5;

ll tag[N << 2], mx[N << 2];

void app(int p, ll h) {
    mx[p] += h;
    tag[p] += h;
}

void down(int p) {
    if (tag[p]) {
        app(ln, tag[p]);
        app(rn, tag[p]);
        tag[p] = 0;
    }
}

void change(int p, int l, int r, int x, int y, ll h) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
        app(p, h);
        return;
    }
    down(p);
    int mid = l + r >> 1;
    change(ln, l, mid, x, y, h);
    change(rn, mid + 1, r, x, y, h);
    mx[p] = max(mx[ln], mx[rn]);
}

ll query(int p, int l, int r, int x, int y) {
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return mx[p];
    int mid = l + r >> 1;
    down(p);
    return max(query(ln, l, mid, x, y), query(rn, mid + 1, r, x, y));
}

struct Node {
    ll x, l, r, op;
    bool operator<(const Node& a) const {
        if (x != a.x)
            return x < a.x;
        else if (l != a.l)
            return l < a.l;
        else
            return op < a.op;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<Node> a, b;
    for (int i = 0; i < n; i++) {
        ll l, r, h;
        cin >> l >> r >> h;
        auto y = query(1, 0, M, l, r - 1);
        a.push_back({l, y, y + h - 1, 0});
        b.push_back({r, y, y + h - 1, 1});
        change(1, 0, M, l, r - 1, h);
    }

    sort(b.begin(), b.end());
    for (int i = 1; i < b.size(); i++) {
        if (b[i].x == b[i - 1].x && b[i].l == b[i - 1].r + 1) {
            b[i].l = b[i - 1].l;
            b[i].r = max(b[i].r, b[i - 1].r);
        } else {
            a.push_back(b[i - 1]);
        }
    }
    a.push_back(b.back());
    sort(a.begin(), a.end());

    vector<Node> stk;
    ll cur = -1, mx = -1;
    for (auto [x, l, r, op] : a) {
        if (op) {
            if (cur == x) {
                l = max(mx + 1, r);
            }
        } else {
            mx = r;
            cur = max(cur, x);
        }
        if (l <= r) stk.push_back({x, l, r, op});
    }

    set<pair<ll, ll>> s;
    int res = 0;

    for (int i = 0; i < stk.size();) {
        ll tag = stk[i].x;
        int j = i;
        while (j < stk.size() && stk[j].x == tag) j++;

        for (int k = i; k < j; k++) {
            auto [x, l, r, op] = stk[k];
            if (op) continue;

            while (1) {
                auto it = s.lower_bound({l, 0});

                if (it == s.end()) break;
                auto [lp, rp] = (*it);
                if (lp > r) break;
                if (rp <= r) {
                    s.erase(it);
                    res++;
                } else {
                    // [r + 1,rp]
                    s.erase(it);
                    s.insert({lp, rp});
                }
            }
            while (1) {
                auto it = s.upper_bound({r, 0});
                if (it == s.begin()) break;
                it = prev(it);
                if (it->second < l) break;
                auto [lp, rp] = (*it);
                s.erase(it);
                s.insert({lp, l - 1});
            }
        }
        for (int k = i; k < j; k++) {
            auto [x, l, r, op] = stk[k];
            if (!op) continue;
            while (1) {
                auto it = s.lower_bound({l, 0});
                if (it == s.end() || it->first > r + 1) break;
                r = max(r, it->second);
                s.erase(it);
            }
            while (1) {
                auto it = s.upper_bound({r, 0});
                if (it == s.begin()) break;
                it = prev(it);
                if (it->second < l - 1) break;
                l = min(l, it->first);
                s.erase(it);
            }
            s.insert({l, r});
        }

        i = j;
        ll v = query(1, 0, M, tag, tag);
        // erase >= v

        while (1) {
            auto it = s.lower_bound({v, 0});
            if (it == s.end()) break;
            s.erase(it);
        }

        // cout << tag << "#\n";
        // for (auto [l, r] : s) cout << l << ' ' << r << endl;
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}

/*
1 1 1 1 0 0 0 0
0 0 0 0 1 1 0 0
0 0 0 0 1 1 0 0
0 1 1 1 1 1 0 0
1 1 1 1 1 1 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0

*/