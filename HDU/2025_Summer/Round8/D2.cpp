#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// 0-index 开区间
template <typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    //[0,x)
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T query(int l, int r) { return sum(r) - sum(l); }

    //[0,x)和小于等于k最大的x
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

// 最小表示法
int get(vector<int> &a) {  // 0-based
    int n = a.size(), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        auto u = a[(i + k) % n];
        auto v = a[(j + k) % n];
        int t = u > v ? 1 : (u < v ? -1 : 0);
        if (t == 0)
            k++;
        else {
            if (t > 0)
                i += k + 1;
            else
                j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}

// 逆序对
ll inv(vector<int> &a) {
    auto b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    Fenwick<int> bit(b.size());
    ll res = 0;
    for (auto k : a) {
        int p = lower_bound(b.begin(), b.end(), k) - b.begin();
        res += bit.query(p + 1, b.size());
        bit.add(p, 1);
    }
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (k == 1) {
        if (a == b) {
            cout << "YES\n";
        } else
            cout << "NO\n";
    } else if (k == n) {
        int i = get(a), j = get(b);
        for (int t = 0; t < n; t++) {
            int x = (i + t) % n;
            int y = (j + t) % n;
            if (a[x] != b[y]) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    } else {
        auto ta = a, tb = b;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if (a == b) {
            int flg = 0;
            for(int i = 0;i < n - 1;i++){
                if(a[i] == a[i + 1]){
                    flg = 1;
                    break;
                }
            }
            if (k % 2 == 0)
                cout << "YES\n";
            else {
                if (inv(ta) % 2 == inv(tb) % 2 || flg)
                    cout << "YES\n";
                else
                    cout << "NO\n";
            }
        } else
            cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}