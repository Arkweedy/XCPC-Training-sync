#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.10 15:45:35

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int n_ = 0) { init(n_); }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }

    void assign(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = std::max(a[i - 1] , v);
        }
    }

    //[0,x)
    T max(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = std::max(ans , a[i - 1]);
        }
        return ans;
    }

    //[l,r)
    //T query(int l, int r) { return sum(r) - sum(l); }

    // 返回 sum(x) 小于等于 k 的最大的 x
    // int select(const T &k) {
    //     int x = 0;
    //     T cur{};
    //     for (int i = 1 << __lg(n); i; i /= 2) {
    //         if (x + i <= n && cur + a[x + i - 1] <= k) {
    //             x += i;
    //             cur = cur + a[x - 1];
    //         }
    //     }
    //     return x;
    // }
};

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n),h(n);
    for(int i = 0;i < n;i++){
        cin >> h[i];
        h[i]--;
    }
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    Fenwick<i64> t(n + 1);
    for(int i = 0;i < n;i++){
        i64 x = t.max(h[i] + 1) + a[i];
        t.assign(h[i], x);
    }
    i64 ans = t.max(n);
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}