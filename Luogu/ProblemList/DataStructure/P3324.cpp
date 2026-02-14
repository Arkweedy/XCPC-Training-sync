#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//P3324.cpp Create time : 2026.02.11 12:58
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using T = int;

struct Node{
    int ls, rs;
    u32 pri;
    T key;
    int sz;
    Node():ls(0),rs(0),pri(rng()),key(),sz(0){}
};

vector<Node>t(1);

struct Treap
{
    int rt = 0;
    //vector<Node>t;

    Treap(){}

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int newNode(T key)
    {
        t.emplace_back();
        t.back().key = key;
        t.back().sz = 1;
        return t.size() - 1;
    }

    int sz(int p)const
    {
        return t[p].sz;
    }

    void push(int p)
    {
        // if(!p)return;
        // if(t[p].rtag == 0)return;
        // if(t[p].ls)apply(t[p].ls, t[p].ktag, t[p].rtag);
        // if(t[p].rs)apply(t[p].rs, t[p].ktag, t[p].rtag);
        // t[p].ktag = t[p].rtag = 0;
    }

    void apply(int p, int a, int b)
    {
        // if(!p)return;
        // t[p].key.first += a;
        // t[p].ktag += a;
        // t[p].res += b;
        // t[p].rtag += b;
        // return;
    }

    void pull(int p)
    {
        if(!p)return;
        t[p].sz = 1 + sz(t[p].ls) + sz(t[p].rs);
        return;
    }

    int merge(int p1, int p2)
    {
        if(!p1 || !p2)return p1 ? p1 : p2;
        if(t[p1].key > t[p2].key)swap(p1,p2);
        if(t[p1].pri < t[p2].pri){
            push(p1);
            t[p1].rs = merge(t[p1].rs, p2);
            pull(p1);
            return p1;
        }
        else{
            push(p2);
            t[p2].ls = merge(p1,t[p2].ls);
            pull(p2);
            return p2;
        }
    }

    pair<int,int> split_less(int p, const T& key){
        if(!p) return {0,0};
        push(p);
        if(t[p].key < key){
            auto [l, r] = split_less(t[p].rs, key);
            t[p].rs = l;
            pull(p);
            return {p, r};
        }else{
            auto [l, r] = split_less(t[p].ls, key);
            t[p].ls = r;
            pull(p);
            return {l, p};
        }
    }

    pair<int,int> split_leq(int p, const T& key){
        if(!p) return {0,0};
        push(p);
        if(!(key < t[p].key)){
            auto [l, r] = split_leq(t[p].rs, key);
            t[p].rs = l;
            pull(p);
            return {p, r};
        }else{
            auto [l, r] = split_leq(t[p].ls, key);
            t[p].ls = r;
            pull(p);
            return {l, p};
        }
    }

    int unite(int a, int b){
        if(!a || !b) return a ? a : b;
        if(t[a].pri > t[b].pri) swap(a, b);
        push(a);
        push(b);
        auto [x, z] = split_leq(b, t[a].key);
        t[a].ls = unite(t[a].ls, x);
        t[a].rs = unite(t[a].rs, z);
        pull(a);
        return a;
    }

    int unite(Treap a){
        if(rt == a.rt)return rt;
        return rt = unite(this->rt, a.rt);
    }

    int insertRoot(int &root, T x)
    {
        auto [a, b] = split_leq(root, x);
        auto [l, m] = split_less(a, x);
        if(m);
        else m = newNode(x);
        root = merge(merge(l, m), b);
        return m;
    }

    void erase(int &root, T x)
    {
        auto [a, b] = split_leq(root, x);
        auto [l, m] = split_less(a, x);
        root = merge(l, b);
        return;
    }

    void extract(int &root, T x)
    {
        auto [a, b] = split_leq(root, x);
        auto [l, m] = split_less(a, x);
        root = merge(l, b);
        return;
    }

    int lower_bound(int &root, T x) //0 base
    {
        auto [a, b] = split_less(root, x);
        int res = sz(a);//0 base
        root = merge(a, b);
        return res;
    }

    int upper_bound(int &root, T x)
    {
        auto [a, b] = split_leq(root, x);
        int res = sz(a);//0 base
        root = merge(a, b);
        return res;
    }

    T kth(int &root, int k) // 1-base
    {
        int p = root;
        if(k <= 0 || k > sz(root))return -1;
        while(1){
            if(sz(t[p].ls) >= k)p = t[p].ls;
            else if(sz(t[p].ls) + 1 >= k)return t[p].key;
            else {k -= sz(t[p].ls) + 1; p = t[p].rs;}
        }
    }

    T prev(int &root, T x)
    {
        auto [a, b] = split_less(root, x);
        T res = kth(a, sz(a));
        root = merge(a, b);
        return res;
    }

    T next(int &root, T x)
    {
        auto [a, b] = split_leq(root, x);
        T res = kth(b, 1);
        root = merge(a, b);
        return res;
    }

    void insert(T x)
    {
        insertRoot(rt, x);
    }

    void erase(T x)
    {
        erase(rt, x);
    }

    void extract(T x)
    {
        extract(rt, x);
    }

    int lower_bound(T x)
    {
        return lower_bound(rt, x);
    }

    int upper_bound(T x)
    {
        return upper_bound(rt, x);
    }

    T prev(T x)
    {
        return prev(rt, x);
    }

    T next(T x)
    {
        return next(rt, x);
    }

    T kth(int x)
    {
        return kth(rt, x);
    }

    T operator[](int x) // 0-base
    {
        return kth(x + 1);
    }

};
class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    int size(int p)
    {
        return sz[find(p)];
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            scc--;
            sz[fu] += sz[fv];
            fa[fv] = fu;
            return true;
        }
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<Treap>t(n);
    DSU dsu(n);
    vector<int>id(n);
    for(int i = 0;i < n;i++){
        int e;
        cin >> e;
        e--;
        t[i].insert(e);
        id[e] = i + 1;
    }
    auto merge = [&](int u, int v)->void
    {
        if(u < 0 || v < 0)return;
        if(dsu.same(u, v))return;
        int ru = dsu.find(u), rv = dsu.find(v);
        dsu.merge(u, v);
        int w = dsu.find(u);
        t[w].rt = t[ru].unite(t[rv]);
        return;
    };
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        merge(u, v);
    }
    int q;
    cin >> q;
    while(q--){
        char op;
        cin >> op;
        int x, y;
        cin >> x >> y;
        if(op == 'Q'){
            x--;
            int fx = dsu.find(x);
            int v = t[fx].kth(y);
            if(v <= -1 || v >= n)cout << -1 << "\n";
            else  cout << id[v] << "\n";
        }
        else{
            x--,y--;
            merge(x, y);
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