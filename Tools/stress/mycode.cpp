#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1712E.cpp Create time : 2026.02.19 02:53

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

    //[l,r)
    T query(int l, int r) { return sum(r) - sum(l); }

    // 返回 sum(x) 小于等于 k 的最大的 x
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

void solve()
{
    int q;
    cin >> q;
    vector<pair<int,int>>qry;
    for(int i =  0;i < q;i++){
        int l, r;
        cin >> l >> r;
        qry.emplace_back(l, r);
    }
    vector<int>id(q);
    iota(id.begin(),id.end(), 0);
    sort(id.begin(),id.end(), [&](int i, int j)->bool
    {
        return qry[i].second == qry[j].second ? qry[i].second < qry[j].second : qry[i].first < qry[j].first;
    });
    //i < j < k
    // a = lcm/i, b, c
    // a + b + c <= 1 , gcd(a, b, c) = 1
    // neg : 2 3 4, 2 3 5

    // ans = \binom{r - l + 1}{3} - [lcm = max] - [2 2 odd] - [2 3 3] - [2 3 4]
    constexpr int N = 1e5;
    Fenwick<i64> t(N + 1);
    vector<vector<int>>fac(N + 1);
    for(int i = 1;i <= N;i++){
        for(int j = 2;i * j <= N;j++){
            fac[i * j].push_back(i);
        }
    }
    auto add = [&](int x)->void
    {
        int n = fac[x].size();
        for(int i = 0;i < n;i++){
            t.add(fac[x][i], n - i - 1);
        }
    };

    int p = 1;
    vector<i64>ans(q);
    for(int i = 0;i < q;i++){
        auto [l, r] = qry[id[i]];
        while(p <= r){
            add(p);
            p++;
        }
        i64 n = r - l + 1;
        i64 res = n * (n - 1) * (n - 2) / 6;
        // 2 3 4 -> 6 4 3
        {
            int a = (l + 1) / 3, b = r / 6;
            if(a <= b && a != 0)res -= b - a + 1;
        }
        // 2 3 5 -> 6, 10, 15
        {
            int a = (l + 6 - 1) / 6, b = r / 15;
            if(a <= b && a != 0)res -= b - a + 1;
        }
        res -= t.query(l, r + 1);
        ans[id[i]] = res;
    }

    for(int i =  0;i < q;i++){
        cout << ans[i] << "\n";
    }
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