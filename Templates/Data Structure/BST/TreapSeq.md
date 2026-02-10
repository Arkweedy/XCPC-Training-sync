维护序列的Treap
支持单点查询(区间聚合值查询也可以实现),区间操作(LazyTag(加，翻转，...)，删除，平移等等)
建树可以$O(n)$使用笛卡尔树的建法(还不会)， 或者一个一个`push_back`过去
使用的rk是**0 base**的，与数组使用对齐
支持查询节点的rank， 如果可以维护val到node id的映射的话，就可以通过val查询rank，从而做到根据val去操作Seq(如把某个val移动到某个rank， 交换两个val， ...)。这在维护的Seq是Permutation时非常好用(一般不会改变很多val-node的对应关系)。需要注意的是如果有影响rank的lazy-tag,查询节点rank前需要先push到该节点的路径。

```c++
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
struct Treap
{
    struct Node{
        int ls, rs;
        u32 pri;
        T val;
        int sz;
        int fa;
        //sums

        //tags
        int rev;
        Node():ls(0),rs(0),pri(rng()),val(),sz(0),fa(0),rev(0){};
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

    void setfa(int s, int p)
    {
        if(s)t[s].fa = p;
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

    void push_path(int p){
        static stack<int> stk;
        while(p){
            stk.push(p);
            p = t[p].fa;
        }
        while(!stk.empty()){
            push(stk.top());
            stk.pop();
        }
    }

    void pull(int p)
    {
        if(p){
            t[p].fa = 0;
            t[p].sz = sz(t[p].ls) + sz(t[p].rs) + 1;
            setfa(t[p].ls, p);
            setfa(t[p].rs, p);
        } 
    }

    void add_tag(int p)
    {
        if(p)t[p].rev ^= 1;
    }

    int merge(int l, int r) // [l, r]
    {
        if(!l || !r)return l ? l : r;
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
        rt = merge(a, d);
    }
    void erase(int l, int r){
        if(l > r) return;
        auto [c, d] = split(rt, r);
        auto [a, b] = split(c, l - 1); // b is the range
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

    int rank(int p)// node i rank
    {
        if(!p)return -1;
        push_path(p);
        //if lazy tag, need push from root to p
        int res = sz(t[p].ls) + 1;
        while(p != 0){
            if(t[t[p].fa].rs == p)res += sz(t[t[p].fa].ls) + 1;
            p = t[p].fa;
        }
        return res - 1;
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
```