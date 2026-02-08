#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using u32 = unsigned int;
using uint = unsigned int;
using u64 = unsigned long long;
using ull = unsigned long long;

using namespace std;

//P5490.cpp Create time : 2026.02.06 23:27

struct segtree
{
    int n;
    vector<int>w;
    vector<int>tree, cnt, len;

    segtree(int n_, vector<int>w_): n(n_), w(w_),tree(n_ * 4), cnt(n_*4), len(n * 4)
    {
        build(0, n - 1, 1);
    }

    void build(int l, int r, int p)
    {
        if(l == r){
            len[p] = w[l];
            return;
        }
        int m = l + r >> 1;
        build(l, m, p * 2);
        build(m + 1, r, p * 2 + 1);
        len[p] = len[p * 2] + len[p * 2 + 1];
        return;
    }

    void apply(int s, int t, int val, int l, int r, int p)
    {
        if(l >= s && r <= t){
            cnt[p] += val;
            if(cnt[p])tree[p] = len[p];
            else{
                if(l == r)tree[p] = 0;
                else push_up(p);
            }
            return;
        }
        int m = l + r >> 1;
        if(m >= s)apply(s, t, val, l ,m, p * 2);
        if(m < t)apply(s, t, val, m + 1, r, p * 2 + 1);
        if(!cnt[p])push_up(p);
        return;
    }

    void push_up(int p)
    {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void apply(int s, int t, int val)
    {
        apply(s, t, val, 0, n - 1, 1);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int>x;
    vector<pair<int,int>>y;
    vector<int>x1(n), x2(n), y1(n), y2(n);
    for(int i = 0;i < n;i++){
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        x.push_back(x1[i]);
        x.push_back(x2[i]);
        y.emplace_back(y1[i], i);
        y.emplace_back(y2[i], i);
    }
    sort(x.begin(),x.end());
    x.erase(unique(x.begin(),x.end()),x.end()); 
    for(int i = 0;i < n;i++){
        x1[i] = lower_bound(x.begin(),x.end(),x1[i]) - x.begin();
        x2[i] = lower_bound(x.begin(),x.end(),x2[i]) - x.begin();
    }

    int m = x.size();
    vector<int>w(m - 1);
    for(int i = 0;i < m - 1;i++){
        w[i] = x[i + 1] - x[i];
    }

   

    segtree t(m - 1, w);
    sort(y.begin(), y.end());


    i64 ans = 0;
    int ny = y[0].first;
    for(auto [v, id] : y){
        ans += 1ll * t.tree[1] * (v - ny);
        int l = x1[id], r = x2[id] - 1;
        if(v == y1[id])t.apply(l, r, 1); 
        else t.apply(l, r, -1);
        ny = v;
    }
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