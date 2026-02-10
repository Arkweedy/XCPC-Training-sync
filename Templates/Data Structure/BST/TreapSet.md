维护多重集的Treap
可以加入区间查询的逻辑， 方法是split出来一个区间 $[L, R]$，然后查询对应的聚合值
函数的默认操作对象是第一个insert节点所在的Treap
可以手动建树(`newNode`一个作为根就行)，可以指定根进行各种操作
`merge`用于不相交值域Treap的合并 
`unite`用于任意Treap的节点合并， 期望复杂度是$O(n)$
进行查询操作前需要确保树非空
sz的类型可以按需改成i64
新加了区间操作，修改了一些地方的push
```c++
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<typename T = pair<int,int>>
struct Treap
{
    struct Node{
        int ls, rs;
        u32 pri;
        T key;
        int sz;
        int cnt;
        
        Node():ls(0),rs(0),pri(rng()),key(),sz(0),cnt(0){}
    };
    
    int rt = 0;
    vector<Node>t;

    Treap():t(1){}
    explicit Treap(size_t n):t(1){t.reserve(n);}

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int newNode(T key)
    {
        t.emplace_back();
        t.back().key = key;
        t.back().cnt = 1;
        t.back().sz = 1;
        return t.size() - 1;
    }

    int newNode(T key, int cnt)
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
        t[p].sz = t[p].cnt + sz(t[p].ls) + sz(t[p].rs);
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
        auto [l, m] = split_less(x, t[a].key);
        if(m){
            t[a].cnt += t[m].cnt;
        }
        t[a].ls = unite(t[a].ls, l);
        t[a].rs = unite(t[a].rs, z);
        pull(a);
        return a;
    }

    int insertRoot(int &root, T x)
    {
        auto [a, b] = split_leq(root, x);
        auto [l, m] = split_less(a, x);
        if(m)t[m].cnt++,pull(m);
        else m = newNode(x);
        root = merge(merge(l, m), b);
        return m;
    }

    void insertRoot(int &root, T x, int c)
    {
        auto [a, b] = split_leq(root, x);
        auto [l, m] = split_less(a, x);
        if(m)t[m].cnt += c, pull(m);
        else m = newNode(x, c);
        root = merge(merge(l, m), b);
        return;
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
        if(t[m].cnt <= 1)root = merge(l, b);
        else{
            t[m].cnt--;
            t[m].sz--;
            root = merge(merge(l, m), b);
        }
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
        if(k <= 0 || k > sz(root))return T();
        while(1){
            if(sz(t[p].ls) >= k)p = t[p].ls;
            else if(sz(t[p].ls) + t[p].cnt >= k)return t[p].key;
            else {k -= sz(t[p].ls) + t[p].cnt; p = t[p].rs;}
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

    void transform(int p, vector<Node>&res)
    {
        push(p);
        if(t[p].ls)transform(t[p].ls, res);
        res.push_back(t[p]);
        if(t[p].rs)transform(t[p].rs, res);
        return;
    }

    vector<Node> transform()
    {
        vector<Node>res;
        transform(rt, res);
        return res;
    }

    vector<Node> transform(int p)
    {
        vector<Node>res;
        if(!p)return res;
        transform(p, res);
        return res;
    }

    void insert(T x)
    {
        insertRoot(rt, x);
    }

    void insert(T x, int c)
    {
        insertRoot(rt, x, c);
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

    // void get(int p, vector<int>&ans)
    // {
    //     push(p);
    //     if(t[p].ls)get(t[p].ls, ans);
    //     ans[t[p].key.second] = t[p].res;
    //     //cerr << "ans : " << t[p].key.second << " " << t[p].res << endl;
    //     if(t[p].rs)get(t[p].rs, ans);
    //     return;
    // }

    void print(int p)
    {
        push(p);
        if(t[p].ls)print(t[p].ls);
        cerr << t[p].res << " ";
        if(t[p].rs)print(t[p].rs);
        return;
    }
};
```