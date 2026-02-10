#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P3919.cpp Create time : 2026.02.08 22:51

struct segtree
{
    int n;
    int vc;
    vector<int>a;
    vector<int>rt, ls, rs;
    vector<int>t;
    

    segtree(int n_):n(n_), vc(0)
    {
        rt.reserve(n * 5);
        ls.reserve(n * 30);
        rs.reserve(n * 30);
        t.reserve(n * 30);
    }

    segtree(int _n, vector<int>& _a):n(_n),vc(0), a(_a)
    {
        rt.reserve(n);
        ls.reserve(n * 20);
        rs.reserve(n * 20);
        t.reserve(n * 20);
        int p = newNode();
        newVersion(p);
        build(0, n - 1, rt[0]);
    }

    void build(int l, int r, int p)
    {
        if(l == r){
            t[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        ls[p] = newNode();
        rs[p] = newNode();
        build(l, m, ls[p]);
        build(m + 1, r, rs[p]);
        push_up(p);
        return;
    }

    void newVersion(int root)
    {
        rt.push_back(root);
        vc++;
    }

    int newNode()
    {
        ls.emplace_back();
        rs.emplace_back();
        t.emplace_back();
        return t.size() - 1;
    }

    int query(int ver, int x)
    {
        return query(x, 0, n - 1, rt[ver]);
    }

    int query(int x, int l, int r, int p)
    {
        if(l == r)return t[p];
        int m = l + r >> 1;
        if(x <= m) return query(x, l, m, ls[p]);
        else return query(x, m + 1, r, rs[p]);
    }

    void apply(int ver, int x, int val)
    {
        newVersion(apply(x, val, 0, n - 1, rt[ver]));
        return;
    }

    void push_up(int p)
    {
        t[p] = t[ls[p]] + t[rs[p]];
    }

    int apply(int x, int val, int l, int r, int p)
    {
        if(l == r){
            int np = newNode();
            t[np] = val;
            return np;
        }
        int m = l + r >> 1;
        int np = newNode();
        if(x <= m){
            int s = apply(x, val, l, m, ls[p]);
            ls[np] = s;
            rs[np] = rs[p];
        }
        else{
            int s = apply(x, val, m + 1, r, rs[p]);
            ls[np] = ls[p];
            rs[np] = s;
        }
        push_up(np);
        return np;
    }

    int query2(int ver, int x)
    {
        auto [res, root] = query2(x, 0, n - 1, rt[ver]);
        newVersion(root);
        return res;
    }

    pair<int,int> query2(int x, int l, int r, int p)
    {
        if(l == r){
            int np = newNode();
            t[np] = t[p];
            return {t[p], p};
        }
        int m = l + r >> 1;
        int np = newNode();
        if(x <= m) {
            auto [res, s] = query2(x, l, m, ls[p]);
            ls[np] = s;
            rs[np] = rs[p];
            return {res, np};
        }
        else {
            auto [res, s] = query2(x, m + 1, r, rs[p]);
            ls[np] = ls[p];
            rs[np] = s;
            return {res, np};
        }
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
    segtree t(n, a);
    while(q--){
        int v, op;
        cin >> v >> op;
        if(op == 1){
            int p, c;
            cin >> p >> c;
            p--;
            t.apply(v, p, c);
        }
        else{
            int p;
            cin >> p;
            p--;
            cout << t.query2(v, p) << "\n";
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