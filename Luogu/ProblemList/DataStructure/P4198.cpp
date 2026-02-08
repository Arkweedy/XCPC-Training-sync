#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P4198.cpp Create time : 2026.02.07 11:23

struct segtree
{
    int n;
    vector<int>tree;
    vector<int>w;

    segtree(int m):n(m),tree(n * 4),w(n * 4){}

    int findfr(int s, int t, int val, int l, int r, int p)
    {
        if(w[p] <= val)return -1;
        if(l >= s && r <= t){
            if(l == r)return l;
            int m = l + r >> 1;
            if(w[p * 2] > val)return findfr(s, t, val, l, m, p * 2);
            else return findfr(s, t, val, m + 1, r, p * 2 + 1);
        }
        int m = l + r >> 1;
        int res = -1;

        if(s <= m)res = findfr(s, t, val, l, m, p * 2);
        if(res != -1)return res;
        else return findfr(s, t, val, m + 1, r, p * 2 + 1);
    }

    int query(int lim, int l, int r, int p)
    {
        if(w[p] <= lim){
            return 0;
        }
        if(l == r){
            return w[p] > lim ? 1 : 0;
        }
        int m = l + r >> 1;
        if(w[p * 2] > lim)return query(lim, l, m, p * 2) + tree[p] - tree[p * 2];
        else return query(lim, m + 1, r, p * 2 + 1);
    }

    void update(int x, int v, int l, int r, int p)
    {
        if(l == r){
            w[p] = v;
            tree[p] = 1;
            return;
        }
        int m = l + r >> 1;
        if(x <= m){
            update(x, v, l, m, p * 2);
        }
        else{
            update(x, v, m + 1, r, p * 2 + 1);
        }
        push_up(p, tree[p * 2] + query(w[p * 2], m + 1, r, p * 2 + 1));
        return;
    }

    void push_up(int p, int v)
    {
        w[p] = max(w[p * 2], w[p * 2 + 1]);
        tree[p] = v;
        return;
    }

    int findfr(int l, int r, int v)
    {
        return findfr(l, r, v, 0, n - 1, 1);
    }

    void update(int x, int val)
    {
        update(x, val, 0, n - 1, 1);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>x(m), y(m);
    vector<pair<int,int>>a;
    for(int i = 0;i < m;i++){
        cin >> x[i] >> y[i];
        int g = gcd(x[i], y[i]);
        a.emplace_back(x[i] / g,y[i] / g);
    }
    auto cmp = [&](pair<int,int>i, pair<int,int>j)->bool
    {
        return 1ll * i.second * j.first < 1ll * i.first * j.second;
    };
    auto eq = [&](pair<int,int>i, pair<int,int>j)->bool
    {
        return i == j;
    };
    sort(a.begin(),a.end(), cmp);
    a.erase(unique(a.begin(),a.end(), eq),a.end());


    segtree t(n + 1);
    for(int i = 0;i < m;i++){
        int g = gcd(x[i], y[i]);
        int v = lower_bound(a.begin(),a.end(), make_pair(x[i] / g, y[i] / g), cmp) - a.begin() + 1;
        t.update(x[i], v);
        cout << t.tree[1] << "\n";
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