维护多重集的Treap
可以加入区间查询的逻辑， 方法是split出来一个区间 $[L, R]$，然后查询对应的聚合值
函数的默认操作对象是第一个insert节点所在的Treap
可以手动建树(`newNode`一个作为根就行)，可以指定根进行各种操作
`merge`用于不相交值域Treap的合并
`unite`用于任意Treap的节点合并，设两棵树的不同key数量为$m\le n$，期望复杂度是$O(m\log(\frac{n}{m}+1))$，可以近似理解为$O(n)$
进行查询操作前需要确保树非空
sz的类型可以按需改成i64
预留了`push`/`apply`位置，需要整体修改key或维护聚合值时按题扩展
`lower_bound`/`upper_bound`/`prev`/`next`默认使用split/merge，代码末尾预留了walk查询备选
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
        // int res = 0;
        // int ktag = 0, rtag = 0;

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

    // void push(int p)
    // {
    //     if(!p)return;
    //     if(t[p].ktag == 0 && t[p].rtag == 0)return;
    //     if(t[p].ls)apply(t[p].ls, t[p].ktag, t[p].rtag);
    //     if(t[p].rs)apply(t[p].rs, t[p].ktag, t[p].rtag);
    //     t[p].ktag = t[p].rtag = 0;
    // }

    // void apply(int p, int a, int b)
    // {
    //     if(!p)return;
    //     t[p].key.first += a;
    //     t[p].ktag += a;
    //     t[p].res += b;
    //     t[p].rtag += b;
    // }

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
            // push(p1);
            t[p1].rs = merge(t[p1].rs, p2);
            pull(p1);
            return p1;
        }else{
            // push(p2);
            t[p2].ls = merge(p1,t[p2].ls);
            pull(p2);
            return p2;
        }
    }

    pair<int,int> split_less(int p, const T& key)
    {
        if(!p)return {0,0};
        // push(p);
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

    pair<int,int> split_leq(int p, const T& key)
    {
        if(!p)return {0,0};
        // push(p);
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

    int unite(int a, int b)
    {
        if(!a || !b)return a ? a : b;
        if(t[a].pri > t[b].pri) swap(a, b);
        // push(a);
        // push(b);
        auto [x, z] = split_leq(b, t[a].key);
        auto [l, m] = split_less(x, t[a].key);
        if(m)t[a].cnt += t[m].cnt;
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
            // push(p);
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

    //walk query
    // int lower_bound_walk(int root, T x)
    // {
    //     int p = root;
    //     int res = 0;
    //     while(p){
    //         // push(p);
    //         if(t[p].key < x){
    //             res += sz(t[p].ls) + t[p].cnt;
    //             p = t[p].rs;
    //         }else p = t[p].ls;
    //     }
    //     return res;
    // }

    // int upper_bound_walk(int root, T x)
    // {
    //     int p = root;
    //     int res = 0;
    //     while(p){
    //         // push(p);
    //         if(!(x < t[p].key)){
    //             res += sz(t[p].ls) + t[p].cnt;
    //             p = t[p].rs;
    //         }else p = t[p].ls;
    //     }
    //     return res;
    // }

    // T prev_walk(int root, T x)
    // {
    //     int p = root;
    //     T res{};
    //     while(p){
    //         // push(p);
    //         if(t[p].key < x){
    //             res = t[p].key;
    //             p = t[p].rs;
    //         }else p = t[p].ls;
    //     }
    //     return res;
    // }

    // T next_walk(int root, T x)
    // {
    //     int p = root;
    //     T res{};
    //     while(p){
    //         // push(p);
    //         if(x < t[p].key){
    //             res = t[p].key;
    //             p = t[p].ls;
    //         }else p = t[p].rs;
    //     }
    //     return res;
    // }

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

};
```

## 接口使用说明

### 基本约定

- 每个不同的`key`只对应一个物理节点，`cnt`记录该`key`的出现次数。
- `sz`维护子树中计入重数后的元素总数，而不是不同`key`数量。
- `rt`是默认操作的根，空树为`0`，`t[0]`是空节点。
- 默认包装接口操作`rt`；带`int &root`的接口可以操作同一节点池中的其他独立根。
- 所有比较按照`T`的`<`和`>`进行。

### 建树与节点接口

| 接口 | 功能 |
| --- | --- |
| `Treap()` | 创建空Treap |
| `Treap(n)` | 创建空Treap并为节点池预留容量 |
| `newNode()` | 分配一个未初始化为有效元素的节点 |
| `newNode(key)` | 创建`key`节点，初始`cnt=sz=1` |
| `newNode(key,cnt)` | 创建重数为`cnt`的`key`节点 |
| `sz(p)` | 返回子树中计入重数的元素总数 |
| `pull(p)` | 根据`cnt`和左右子树重算`sz` |

通常直接使用默认根包装：

```c++
Treap<int> t(q + 1);
t.insert(x);
```

需要维护多棵树时，在同一个`Treap`对象中保存多个根：

```c++
Treap<int> t;
int a = 0, b = 0;
t.insertRoot(a, x);
t.insertRoot(b, y);
```

### 值域拆分与合并

```c++
pair<int,int> split_less(int p, const T& key);
```

返回：

```text
左树：所有key < key
右树：所有key >= key
```

```c++
pair<int,int> split_leq(int p, const T& key);
```

返回：

```text
左树：所有key <= key
右树：所有key > key
```

```c++
int merge(int a, int b);
```

合并两棵值域严格不相交的Treap。允许参数顺序相反，但必须满足一棵树的全部`key`严格小于另一棵树的全部`key`。`merge`不会合并相同`key`的节点。

```c++
int unite(int a, int b);
```

合并同一节点池中两棵任意值域的独立Treap，相同`key`的`cnt`会相加。调用后应只继续使用返回的新根：

```c++
int root = t.unite(a, b);
```

设两棵树的不同`key`数量为$m\le n$，`unite`期望复杂度为：

```text
O(m log(n/m+1))
```

比赛时可以先近似理解为$O(n)$级别的整树合并。

### 插入与删除

| 接口 | 功能 |
| --- | --- |
| `insertRoot(root,x)` | 向指定根插入一个`x`，返回对应节点编号 |
| `insertRoot(root,x,c)` | 向指定根加入`c`个`x` |
| `erase(root,x)` | 从指定根删除`x`的全部副本 |
| `extract(root,x)` | 从指定根删除`x`的一个副本 |
| `insert(x)` | 对默认根插入一个`x` |
| `insert(x,c)` | 对默认根加入`c`个`x` |
| `erase(x)` | 从默认根删除`x`的全部副本 |
| `extract(x)` | 从默认根删除`x`的一个副本 |

`erase`和`extract`沿用`std::multiset`式区分：

```text
erase(x)   -> 删除全部x
extract(x) -> 删除一个x
```

### rank与顺序统计

| 接口 | 下标约定 | 功能 |
| --- | --- | --- |
| `lower_bound(root,x)` | 0-based | 返回指定树中`<x`的元素总数 |
| `upper_bound(root,x)` | 0-based | 返回指定树中`<=x`的元素总数 |
| `kth(root,k)` | 1-based | 返回指定树的第`k`小 |
| `prev(root,x)` | - | 返回严格小于`x`的最大`key` |
| `next(root,x)` | - | 返回严格大于`x`的最小`key` |
| `lower_bound(x)` | 0-based | 默认根版本 |
| `upper_bound(x)` | 0-based | 默认根版本 |
| `kth(k)` | 1-based | 默认根版本 |
| `operator[](i)` | 0-based | 返回默认树的第`i`小 |
| `prev(x)` | - | 默认根版本 |
| `next(x)` | - | 默认根版本 |

查询`x`在多重集中的重数：

```c++
int cnt = t.upper_bound(x) - t.lower_bound(x);
```

查询题目中常见的1-based排名：

```c++
int rank = t.lower_bound(x) + 1;
```

两种第$k$小写法：

```c++
T a = t.kth(k); // k为1-based
T b = t[k - 1]; // 下标为0-based
```

### 可选lazy扩展

默认代码不启用`push/apply`。需要类似702F的整棵`key`修改和答案标记时，解除以下代码的注释：

- `Node::res`、`Node::ktag`、`Node::rtag`；
- `push`和`apply`；
- `merge`、`split_less`、`split_leq`、`unite`中的`push`；
- 如果查询过程中也可能存在未下传标记，再解除`kth`中的`push(p)`。

当前注释示例针对`T=pair<int,int>`：

```text
key.first += a
res       += b
```

使用其他`T`或其他聚合值时，应按题修改`Node`字段和`apply`内容。整体修改`key`后必须保证子树内部的BST顺序仍然成立。

### walk查询备选

默认`lower_bound`、`upper_bound`、`prev`、`next`通过`split/merge`实现。代码中的注释区域还提供：

- `lower_bound_walk`；
- `upper_bound_walk`；
- `prev_walk`；
- `next_walk`。

解除注释后可以直接沿BST查询，减少拆树和合树的常数：

```c++
int rank = t.lower_bound_walk(t.rt, x);
T pre = t.prev_walk(t.rt, x);
```

walk版本与默认版本的返回语义完全一致。如果同时启用lazy，还需要解除各walk函数内部`push(p)`的二层注释。

### 复杂度

设当前不同`key`数量为$n$：

| 操作 | 期望复杂度 |
| --- | --- |
| `insert`、`erase`、`extract` | $O(\log n)$ |
| `lower_bound`、`upper_bound`、`kth`、`prev`、`next` | $O(\log n)$ |
| `split_less`、`split_leq`、`merge` | $O(\log n)$ |
| `unite` | $O(m\log(\frac{n}{m}+1))$，$m\le n$ |

Treap退化时单次普通操作最坏为$O(n)$。
