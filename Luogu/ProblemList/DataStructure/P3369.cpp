#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P3369.cpp Create time : 2026.02.09 22:07

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Treap
{
    struct Node{
        int ls, rs;
        u32 pri;
        int key;
        int sz;
        int cnt;
        Node():ls(0),rs(0),pri(rng()),key(0), sz(0), cnt(0){}
    };
    
    int rt = 1;
    vector<Node>t;

    Treap():t(1){}

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int newNode(int key)
    {
        t.emplace_back();
        t.back().key = key;
        t.back().cnt = 1;
        t.back().sz = 1;
        return t.size() - 1;
    }

    int newNode(int key, int cnt)
    {
        t.emplace_back();
        t.back().key = key;
        t.back().cnt = cnt;
        t.back().sz = cnt;
        return t.size() - 1;
    }

    int sz(int p)const
    {
        return t[p].sz;
    }

    void pull(int p)
    {
        t[p].sz = t[p].cnt + sz(t[p].ls) + sz(t[p].rs);
        return;
    }

    int merge(int p1, int p2)
    {
        if(!p1 || !p2)return p1 ? p1 : p2;
        if(t[p1].key > t[p2].key)swap(p1,p2);
        if(t[p1].pri < t[p2].pri){
            t[p1].rs = merge(t[p1].rs, p2);
            pull(p1);
            return p1;
        }
        else{
            t[p2].ls = merge(t[p2].ls, p1);
            pull(p2);
            return p2;
        }
    }

    pair<int,int>split_key(int p, int key)
    {
        if(p == 0)return {0, 0};
        if(t[p].key <= key){
            auto [l, r] = split_key(t[p].rs, key);
            t[p].rs = l;
            pull(p);
            return {p, r};
        }
        else{
            auto [l, r] = split_key(t[p].ls, key);
            t[p].ls = r;
            pull(p);
            return {l, p};
        }
    }

    // pair<int,int>split_rk(int p, int rk)
    // {
    //     if(p == 0)return {0, 0};
    //     if(sz(t[p].ls) + t[p].cnt <= rk){
    //         auto [l, r] = split_rk(t[p].rs, rk - sz(t[p].ls) - t[p].cnt);
    //         t[p].rs = l;
    //         pull(p);
    //         return {p, r};
    //     }
    //     else{
    //         auto [l, r] = split_rk(t[p].ls, rk);
    //         t[p].ls = r;
    //         pull(p);
    //         return {l, p};
    //     }
    // }

    void insert(int &root, int x)
    {
        auto [a, b] = split_key(root, x);
        auto [l, m] = split_key(a, x - 1);
        if(m)t[m].cnt++, t[m].sz++;
        else m = newNode(x);
        root = merge(merge(l, m), b);
        return;
    }

    void insert(int &root, int x, int c)
    {
        auto [a, b] = split_key(root, x);
        auto [l, m] = split_key(a, x - 1);
        if(m)t[m].cnt += c, t[m].sz += c;
        else m = newNode(x);
        root = merge(merge(l, m), b);
        return;
    }

    void erase(int &root, int x)
    {
        auto [a, b] = split_key(root, x);
        auto [l, m] = split_key(a, x - 1);
        root = merge(l, b);
        return;
    }

    void extract(int &root, int x)
    {
        auto [a, b] = split_key(root, x);
        auto [l, m] = split_key(a, x - 1);
        if(t[m].cnt <= 1)root = merge(l, b);
        else{
            t[m].cnt--;
            t[m].sz--;
            root = merge(merge(l, m), b);
        }
        return;
    }

    int lower_bound(int &root, int x) //0 base
    {
        auto [a, b] = split_key(root, x - 1);
        int res = sz(a);//0 base
        root = merge(a, b);
        return res;
    }

    int upper_bound(int &root, int x)
    {
        auto [a, b] = split_key(root, x);
        int res = sz(a) - 1;//0 base
        root = merge(a, b);
        return res;
    }

    int rk(int &root, int k) // tree
    {
        int p = root;
        if(k <= 0 || k > sz(root))return -1;
        while(1){
            if(sz(t[p].ls) >= k)p = t[p].ls;
            else if(sz(t[p].ls) + t[p].cnt >= k)return t[p].key;
            else {k -= sz(t[p].ls) + t[p].cnt; p = t[p].rs;}
        }
    }

    int prev(int &root, int x)
    {
        auto [a, b] = split_key(root, x - 1);
        int res = rk(a, sz(a));
        root = merge(a, b);
        return res;
    }

    int next(int &root, int x)
    {
        auto [a, b] = split_key(root, x);
        int res = rk(b, 1);
        root = merge(a, b);
        return res;
    }
};


void solve()
{
    int n;
    cin >> n;
    Treap t;
    int root = 0;
    for(int i = 0;i < n;i++){
        int op, x;
        cin >> op >> x;
        if(op == 1){
            if(root == 0){
                root = t.newNode(x);
            }
            else{
                t.insert(root, x);
            }
        }
        else if(op == 2){
            t.extract(root, x);
        }
        else if(op == 3){
            int res = t.lower_bound(root, x) + 1;
            cout << res << "\n";
        }
        else if(op == 4){
            int res = t.rk(root, x);
            cout << res << "\n";
        }
        else if(op == 5){
            int res = t.prev(root, x);
            cout << res << "\n";
        }
        else if(op == 6){
            int res = t.next(root, x);
            cout << res << "\n";
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