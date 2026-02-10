#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P3391.cpp Create time : 2026.02.10 02:42

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
struct Treap
{
    struct Node{
        int ls, rs;
        u32 pri;
        T val;
        int sz;
        //sums

        //tags
        int rev;
        Node():ls(0),rs(0),pri(rng()),val(),sz(0),rev(false){};
    };

    int rt = 0;
    vector<Node>t;

    Treap():t(1){};

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int newNode(T val)
    {
        t.emplace_back();
        t.back().val = val;
        t.back().sz = 1;
        return t.size() - 1;
    }

    int sz(int p)const
    {
        return t[p].sz;
    }

    void push(int p)
    {
        if(p && t[p].rev){
            swap(t[p].ls, t[p].rs);
            add_tag(t[p].ls);
            add_tag(t[p].rs);
            t[p].rev = 0;
        }
    }

    void pull(int p)
    {
        if(p)t[p].sz = sz(t[p].ls) + sz(t[p].rs) + 1;
    }

    void add_tag(int p)
    {
        if(p)t[p].rev ^= 1;
    }

    int merge(int l, int r) // [l, r]
    {
        if(!l || !r)return l ? l : r;
        //if(t[l].key > t[r].key)swap(l,r);
        if(t[l].pri < t[r].pri){
            push(l);
            t[l].rs = merge(t[l].rs, r);
            pull(l);
            return l;
        }
        else{
            push(r);
            t[r].ls = merge(l, t[r].ls);
            pull(r);
            return r;
        }
    }

    pair<int,int> split(int p, int rk){ //rk base 0, split to [0, rk], [rk + 1, sz - 1]
        if(!p) return {0,0};
        if(rk < 0) return {0, p};
        if(rk >= sz(p) - 1)return {p, 0};
        push(p);
        if(sz(t[p].ls) + 1 <= rk + 1){
            auto [l, r] = split(t[p].rs, rk - sz(t[p].ls) - 1);
            t[p].rs = l;
            pull(p);
            return {p, r};
        }else{
            auto [l, r] = split(t[p].ls, rk);
            t[p].ls = r;
            pull(p);
            return {l, p};
        }
    }

    void push_back(T val)
    {
        int c = newNode(val);
        rt = merge(rt, c);
        return;
    }

    void insert(T val, int rk) // insert as rk , base 0
    {
        auto [l, r] = split(rt, rk);
        int c = newNode(val);
        rt = merge(merge(l, c), r);
        return;
    }

    void erase(int rk){
        auto [c, d] = split(rt, rk);
        auto [a, b] = split(c, rk - 1); // b is single node
        // recycle(b) 可选
        rt = merge(a, d);
    }
    void erase(int l, int r){
        if(l > r) return;
        auto [c, d] = split(rt, r);
        auto [a, b] = split(c, l - 1); // b is the range
        // recycle subtree b 可选
        rt = merge(a, d);
    }

    void apply(int l, int r)
    {
        if(r < l)return;
        auto [c, d] = split(rt, r);
        auto [a, b] = split(c, l - 1);
        add_tag(b);
        rt = merge(merge(a, b), d);
        return;
    }

    T query(int rk)//base 0
    {
        auto [c, d] = split(rt, rk);
        auto [a, b] = split(c, rk - 1);
        T res = t[b].val;
        rt = merge(merge(a, b), d);
        return res;
    }

    vector<T> transform()
    {
        vector<T>res;
        transform(rt, res);
        return res;
    }

    void transform(int p, vector<T>&res)
    {
        push(p);
        if(t[p].ls)transform(t[p].ls, res);
        res.push_back(t[p].val);
        if(t[p].rs)transform(t[p].rs, res);
        return;
    }

    void print(int p)
    {
        push(p);
        if(t[p].ls)print(t[p].ls);
        cerr << t[p].val << " ";
        if(t[p].rs)print(t[p].rs);
        return;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    Treap<int> t;
    for(int i = 0;i < n;i++){
        t.push_back(i + 1);
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        t.apply(l, r);
    }
    auto ans = t.transform();
    for(auto e : ans){
        cout << e << " ";
    }
    cout << endl;
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