#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.04.11 22:13:14

struct segtree
{
    int n;
    int vc;
    vector<int>a;
    vector<int>rt, ls, rs;
    vector<i64>t;
    

    segtree(int n_):n(n_), vc(0)
    {
        rt.reserve(n * 5);
        ls.reserve(n * 30);
        rs.reserve(n * 30);
        t.reserve(n * 30);
    }

    segtree(int _n, vector<int> _a):n(_n),vc(0), a(_a)
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
            t[p] = 0;
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

    int newVersion(int root)
    {
        rt.push_back(root);
        vc++;
        return vc - 1;
    }

    int newNode()
    {
        ls.emplace_back();
        rs.emplace_back();
        t.emplace_back();
        return t.size() - 1;
    }

    // int query(int ver, int x)
    // {
    //     return query(x, 0, n - 1, rt[ver]);
    // }

    // int query(int x, int l, int r, int p)
    // {
    //     if(l == r)return t[p];
    //     int m = l + r >> 1;
    //     if(x <= m) return query(x, l, m, ls[p]);
    //     else return query(x, m + 1, r, rs[p]);
    // }

    int apply(int ver, int x, int val)
    {
        return newVersion(apply(x, val, 0, n - 1, rt[ver]));
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

    int kth(int l, int r, int k)
    {
        int lp = rt[l], rp = rt[r + 1];
        return binary_find(lp, rp, 0, n - 1, k);
    }

    i64 query(int s, int st, int l, int r, int p)
    {
        if(s <= l && r <= st){
            return t[p];
        }
        else{
            int m = l + r >> 1;
            i64 res = 0;
            if(ls[p] && s <= m)res += query(s, st, l, m, ls[p]);
            if(rs[p] && m < st)res += query(s, st, m + 1, r, rs[p]);
            return res;
        }
    }=

    int binary_find(int lp, int rp,int l, int r, int k)
    {
        if(l == r)return l;
        int m = l + r >> 1;
        int lc = t[ls[rp]] - t[ls[lp]];
        if(lc >= k)return binary_find(ls[lp], ls[rp], l, m, k);
        else return binary_find(rs[lp],rs[rp], m + 1, r, k - lc);
    }

    i64 query(int ver, int l, int r)
    {
        return query(l, r, 0, n - 1, rt[ver]);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>rt(n);
    segtree t(m);
    int r = t.newNode();
    t.newVersion(r);
    //cerr << "ok" << r << endl;
    t.build(0, m - 1, r);
    //cerr << "ok" << endl;
    
    int q;
    cin >> q;
    while(q--){
        //cerr << q << endl;
        int op;
        cin >> op;
        if(op == 1){
            int x, y;
            cin >> x >> y;
            x--,y--;
            rt[x] = rt[y];
        }
        else if(op == 2){
            int x, y, z;
            cin >> x >> y >> z;
            x--,y--;
            rt[x] = t.apply(rt[x], y, z);
        }
        else{
            int x, l, r;
            cin >> x >> l >> r;
            x--,l--,r--;
            i64 res = t.query(rt[x], l, r);
            cout << res << endl;
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