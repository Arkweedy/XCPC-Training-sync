#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.02.15 16:37

constexpr int inf = 1e9;

struct segtree
{
    int n;
    vector<int>ma, mi, a;
    vector<i64>c;

    segtree(vector<int>vec) : n(vec.size()), ma(n * 4), mi(n * 4), c(n * 4), a(vec)
    {
        build(0, n - 1, 1);
    }

    void build(int l, int r, int p)
    {
        if(l == r){
            c[p] = ma[p] = mi[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        build(l, m, p * 2);
        build(m + 1, r, p * 2 + 1);
        pull(p);
        return;
    }

    void pull(int p)
    {
        ma[p] = max(ma[p * 2], ma[p * 2 + 1]);
        mi[p] = min(mi[p * 2], mi[p * 2 + 1]);
        c[p] = c[p * 2] + c[p * 2 + 1];
        return;
    }

    void push(int p)
    {
        if(c[p] == 0){
            c[p * 2] = 0;
            mi[p * 2] = inf;
            ma[p * 2] = 0;
            c[p * 2 + 1] = 0;
            mi[p * 2 + 1] = inf;
            ma[p * 2 + 1] = 0;
        }
    }

    i64 apply(int s, int t, int k, int l, int r, int p)
    {
        if(c[p] == 0)return 0;
        if(l >= s && r <= t){
            i64 res = 0;
            if(mi[p] >= k){
                res = c[p];
                c[p] = 0;
                mi[p] = inf;
                ma[p] = 0;
            }
            else if(ma[p] >= k){
                int m = l + r >> 1;
                push(p);
                if(ma[p * 2] >= k)res += apply(s, t, k, l, m, p * 2);
                if(ma[p * 2 + 1] >= k)res += apply(s, t, k, m + 1, r, p * 2 + 1);
                pull(p);
            }
            return res;
        }
        int m = l + r >> 1;
        i64 res = 0;
        push(p);
        if(s <= m)res += apply(s, t, k, l, m, p * 2);
        if(t > m)res += apply(s, t, k, m + 1, r, p * 2 + 1);
        pull(p);
        return res;
    }

    i64 apply(int l, int r, int val)
    {
        return apply(l, r, val, 0, n - 1, 1);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    segtree t(a);
    while(q--){
        int l, r, k;
        cin >> l >> r >> k;
        l--,r--;
        cout << t.apply(l, r, k) << "\n";
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