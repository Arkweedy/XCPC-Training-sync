#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.05.18 23:51

struct segtree{
    int n;
    vector<int>t;
    vector<int>lz;

    const int inf = 1e9;
    segtree(int n_){
        n = n_;
        t.resize(n * 4, inf);
        lz.resize(n * 4, inf);
    }

    void push(int p)
    {
        if(lz[p] != inf){
            t[p * 2] = min(t[p * 2], lz[p]);
            t[p * 2 + 1] = min(t[p * 2 + 1], lz[p]);
            lz[p * 2] = min(lz[p * 2], lz[p]);
            lz[p * 2 + 1] = min(lz[p * 2 + 1], lz[p]);
            lz[p] = inf;
        }
    }

    int query(int x, int l, int r, int p)
    {
        if(l == r)return t[p];
        int m = l + r >> 1;
        push(p);
        if(x <= m)return query(x, l, m, p * 2);
        else return query(x, m + 1, r, p * 2 + 1);
    }

    void apply(int s, int tt, int v, int l, int r, int p)
    {
        if(s <= l && r <= tt){
            t[p] = min(t[p], v);
            lz[p] = min(lz[p], v);
            return;
        }
        int m = l + r >> 1;
        push(p);
        if(s <= m)apply(s, tt, v, l, m, p * 2);
        if(tt > m)apply(s, tt, v, m + 1, r, p * 2 + 1);
        return;
    }

    int query(int x)
    {
        return query(x, 0, n - 1, 1);
    }

    void rangeApply(int l, int r, int v)
    {
        return apply(l, r, v, 0, n - 1, 1);
    }
};

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
    constexpr int N = 1e6;
    int n;
    cin >> n;
    vector<int>a(n), b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
    }

    int m;
    cin >> m;
    vector<int>c(m), d(m), e(m);
    for(int i = 0;i < m;i++){
        cin >> c[i];
    }
    for(int i = 0;i < m;i++){
        cin >> d[i];
    }
    for(int i = 0;i < m;i++){
        cin >> e[i];
    }

    vector<int>ida(n),idb(n),idc(m),idd(m);
    iota(ida.begin(),ida.end(), 0);
    iota(idc.begin(),idc.end(), 0);
    iota(idb.begin(),idb.end(), 0);
    iota(idd.begin(),idd.end(), 0);
    sort(ida.begin(),ida.end(), [&](int i, int j)->bool
    {
        return a[i] < a[j];
    });
    sort(idb.begin(),idb.end(), [&](int i, int j)->bool
    {
        return b[i] < b[j];
    });
    sort(idc.begin(),idc.end(), [&](int i, int j)->bool
    {
        return c[i] < c[j];
    });
    sort(idd.begin(),idd.end(), [&](int i, int j)->bool
    {
        return d[i] < d[j];
    });

    constexpr int inf = 1e9;
    segtree tc(m), td(m);
    vector<int>ans(m, inf);

    int pc = 0;
    for(int i = 0;i < n;i++){
        int x = ida[i];
        while(pc < m && c[idc[pc]] <= a[x]){
            tc.rangeApply(pc ,pc , d[idc[pc]] + e[idc[pc]]);
            pc++;
        }
        tc.rangeApply(0, pc - 1, a[x] + b[x]);
        tc.rangeApply(pc, m - 1, b[x]);
    }

    int pd = 0;
    for(int i = 0;i < n;i++){
        int x = idb[i];
        while(pd < m && d[idd[pd]] <= b[x]){
            td.rangeApply(pd ,pd , c[idd[pd]] + e[idd[pd]]);
            pd++;
        }
        td.rangeApply(0, pd - 1, a[x] + b[x]);
        td.rangeApply(pd, m - 1, a[x]);
    }

    for(int i = 0;i < m;i++){
        int x = tc.query(i);
        int y = td.query(i);
        ans[idc[i]] = min(ans[idc[i]], x);
        ans[idd[i]] = min(ans[idd[i]], y);
    }


    Fenwick<int>f(N + 1);
    int pa = 0;
    for(int i = 0;i < m;i++){
        int x = idc[i];
        while(pa < n && a[ida[pa]] < c[x]){
            int id = ida[pa];
            f.add(b[id], 1);
            pa++;
        }
        int cnt = f.query(0, d[x]);
        if(cnt >= 1)ans[x] = 0;
    }

    for(int i = 0;i < m;i++){
        ans[i] = min(ans[i], c[i] + d[i] + e[i] * 2);
    }

    for(int i = 0;i < m;i++){
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