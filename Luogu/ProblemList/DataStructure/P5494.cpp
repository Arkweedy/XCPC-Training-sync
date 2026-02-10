#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P5494.cpp Create time : 2026.02.09 15:50

using info = i64;

vector<int>ls(1), rs(1);
vector<info>t(1);
stack<int>rec;

struct segtree
{
    int n;
    int root;

    segtree():n(0),root(-1){}

    segtree(int n_) = delete;

    void init(int n_)
    {
        n = n_;
        root = newNode();
    }

    int newNode()
    {
        if(!rec.empty()){
            int p = rec.top();
            rec.pop();
            return p;
        }
        else{
            t.emplace_back();
            ls.emplace_back();
            rs.emplace_back();
            return t.size() - 1;
        }
    }

    void apply(int x, int v)
    {
        apply(x, v, 0, n - 1, root);
    }

    void push_up(int p)
    {
        t[p] = info();
        if(ls[p])t[p] = t[p] + t[ls[p]];
        if(rs[p])t[p] = t[p] + t[rs[p]];
        return;
    }

    void recycle(int p)
    {
        t[p] = info();
        ls[p] = rs[p] = 0;
        rec.push(p);
        return;
    }

    void apply(int x, int v, int l, int r, int p)
    {
        if(l == r){
            t[p] += v;
            return;
        }
        int m = l + r >> 1;
        if(x <= m){
            if(ls[p] == 0)ls[p] = newNode();
            apply(x, v, l, m, ls[p]);
        }
        else{
            if(rs[p] == 0)rs[p] = newNode();
            apply(x, v, m + 1, r, rs[p]);
        }
        push_up(p);
        return;
    }

    void join(segtree& ot)
    {
        assert(ot.n == n);
        join(root, ot.root, 0, n - 1);
        return;
    }

    void join(int p1, int p2, int l, int r)
    {
        if(l == r){
            t[p1] += t[p2];
            recycle(p2);
            return;
        }
        int m = l + r >> 1;
        if(ls[p1] && ls[p2])join(ls[p1], ls[p2], l, m);
        else if(ls[p2])ls[p1] = ls[p2];
        if(rs[p1] && rs[p2])join(rs[p1], rs[p2], m + 1, r);
        else if(rs[p2])rs[p1] = rs[p2];
        push_up(p1);
        recycle(p2);
        return;
    }

    segtree split(int l, int r)
    {
        segtree nt;
        nt.init(n);
        split(l, r, root, nt.root, 0, n - 1);
        return nt;
    }

    int split(int L, int R, int p1, int p2, int l, int r)
    {
        if(l >= L && r <= R){
            t[p2] = t[p1];
            ls[p2] = ls[p1];
            rs[p2] = rs[p1];
            recycle(p1);
            return 1;
        }
        int m = l + r >> 1;
        if(L <= m && ls[p1]){
            ls[p2] = newNode();
            if(split(L, R, ls[p1], ls[p2], l, m))ls[p1] = 0;
        }
        if(R > m && rs[p1]){
            rs[p2] = newNode();
            if(split(L, R, rs[p1], rs[p2], m + 1, r))rs[p1] = 0;
        }
        push_up(p1);
        push_up(p2);
        return 0;
    }

    info query(int l, int r)
    {
        return query(l, r, 0, n - 1, root);
    }

    info query(int L, int R, int l, int r, int p)
    {
        if(l >= L && r <= R){
            return t[p];
        }
        info res = 0;
        int m = l + r >> 1;
        if(L <= m && ls[p])res += query(L, R, l, m, ls[p]);
        if(m < R && rs[p])res += query(L, R, m + 1, r, rs[p]);
        return res;
    }

    int kth(i64 k)//all
    {
        if(k <= 0 || k > t[root])return -1;
        return binary_find(k, 0, n - 1, root);
    }

    int binary_find(i64 k, int l, int r, int p)//0 ~ n - 1
    {
        if(l == r){
            return l;
        }
        int m = l + r >> 1;
        if(ls[p] && t[ls[p]] >= k)return binary_find(k, l, m, ls[p]);
        else if(ls[p])k -= t[ls[p]];
        return binary_find(k, m + 1, r, rs[p]);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<segtree>t;
    t.emplace_back();
    t[0].init(n);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        t[0].apply(i, x);
    }
    while(q--){
        int op;
        cin >> op;
        if(op == 0){
            int p, x, y;
            cin >> p >> x >> y;
            p--,x--,y--;
            t.push_back(t[p].split(x, y));
        }
        else if(op == 1){
            int x, y;
            cin >> x >> y;
            x--,y--;
            t[x].join(t[y]);
        }
        else if(op == 2){
            int p, x, y;
            cin >> p >> x >> y;
            p--,y--;
            t[p].apply(y, x);
        }
        else if(op == 3){
            int p, x, y;
            cin >> p >> x >> y;
            p--,x--,y--;
            cout << t[p].query(x, y) << "\n";
        }
        else if(op == 4){
            i64 p, k;
            cin >> p >> k;
            p--;
            int res = t[p].kth(k);
            if(res == -1)cout << res << "\n";
            else cout << res + 1 << "\n";
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