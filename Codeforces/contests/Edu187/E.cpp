#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.25 23:37

// e(i) = 1/(n-2) max(\sum_j < i |aj - ai - 1|, \sum_j > i aj - ai+1)

// a ds

// binary

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

constexpr int P = 998244353;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    // find l, r
    vector<i64>sa = a;
    sort(sa.begin(),sa.end());
    for(int i = 0;i < n;i++){
        a[i] = lower_bound(sa.begin(),sa.end(), a[i]) - sa.begin();
    }

    Fenwick<i64>f(n);
    Fenwick<int>rk(n);

    set<i64>st;
    st.insert(-1);
    st.insert(n);
    int all = 0;

    auto calc = [&](int p)->pair<i64, i64> // p->rk
    {
        int k = rk.select(p);// val
        i64 pre = *prev(st.lower_bound(k));
        i64 nxt = *next(st.lower_bound(k));
        //cerr << pre << " " << nxt << endl;
        i64 l = sa[pre] * p - f.query(0, k);
        i64 r = f.query(k + 1, n) - sa[nxt] * (all - p - 1);
        return {l, r};
    };

    for(int i = 0;i < n;i++){
        all++;
        st.insert(a[i]);
        f.add(a[i], sa[a[i]]);
        rk.add(a[i], 1);
        if(i >= 2){
            int l = 0, r = i;
            while(r - l > 1){
                int m = l + r >> 1;
                auto [ls, rs] = calc(m);//rk
                if(ls <= rs)l = m;
                else r = m;
            }
            i64 ans = min(calc(l).second, calc(r).first) % P * power(i + 1 - 2, P - 2) % P;
            cout << ans << "\n";
        }
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