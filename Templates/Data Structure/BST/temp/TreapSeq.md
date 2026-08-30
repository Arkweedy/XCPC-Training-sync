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
        // i64 w = 0, sum = 0;

        //tags
        // int rev = 0;

        Node():ls(0),rs(0),pri(rng()),val(),sz(0),fa(0){};
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
        // t.back().w = 1;
        // t.back().sum = 1;
        return t.size() - 1;
    }

    // int newNode(T val, i64 w)
    // {
    //     t.emplace_back();
    //     t.back().val = val;
    //     t.back().sz = 1;
    //     t.back().w = w;
    //     t.back().sum = w;
    //     return t.size() - 1;
    // }

    int sz(int p)const
    {
        return t[p].sz;
    }

    // i64 sum(int p)const
    // {
    //     return t[p].sum;
    // }

    void setfa(int s, int p)
    {
        if(s)t[s].fa = p;
    }

    // void push(int p)
    // {
    //     if(p && t[p].rev){
    //         swap(t[p].ls, t[p].rs);
    //         add_tag(t[p].ls);
    //         add_tag(t[p].rs);
    //         t[p].rev = 0;
    //     }
    // }

    // void push_path(int p)
    // {
    //     static stack<int> stk;
    //     while(p){
    //         stk.push(p);
    //         p = t[p].fa;
    //     }
    //     while(!stk.empty()){
    //         push(stk.top());
    //         stk.pop();
    //     }
    // }

    void pull(int p)
    {
        if(!p)return;
        t[p].sz = sz(t[p].ls) + sz(t[p].rs) + 1;
        // t[p].sum = sum(t[p].ls) + t[p].w + sum(t[p].rs);
        setfa(t[p].ls, p);
        setfa(t[p].rs, p);
    }

    // void add_tag(int p)
    // {
    //     if(p)t[p].rev ^= 1;
    // }

    int merge(int l, int r) // [l, r]
    {
        if(!l || !r){
            int p = l ? l : r;
            setfa(p, 0);
            return p;
        }
        if(t[l].pri < t[r].pri){
            // push(l);
            t[l].rs = merge(t[l].rs, r);
            pull(l);
            setfa(l, 0);
            return l;
        }else{
            // push(r);
            t[r].ls = merge(l, t[r].ls);
            pull(r);
            setfa(r, 0);
            return r;
        }
    }

    pair<int,int> split(int p, int rk) //rk base 0, split to [0, rk], [rk + 1, sz - 1]
    {
        if(!p)return {0,0};
        if(rk < 0){
            setfa(p, 0);
            return {0, p};
        }
        if(rk >= sz(p) - 1){
            setfa(p, 0);
            return {p, 0};
        }
        // push(p);
        if(sz(t[p].ls) + 1 <= rk + 1){
            auto [l, r] = split(t[p].rs, rk - sz(t[p].ls) - 1);
            t[p].rs = l;
            pull(p);
            setfa(p, 0);
            setfa(r, 0);
            return {p, r};
        }else{
            auto [l, r] = split(t[p].ls, rk);
            t[p].ls = r;
            pull(p);
            setfa(l, 0);
            setfa(p, 0);
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

    // void apply(int l, int r)
    // {
    //     if(r < l)return;
    //     auto [c, d] = split(rt, r);
    //     auto [a, b] = split(c, l - 1);
    //     add_tag(b);
    //     rt = merge(merge(a, b), d);
    // }

    T query(int rk)//base 0
    {
        auto [c, d] = split(rt, rk);
        auto [a, b] = split(c, rk - 1);
        T res = t[b].val;
        rt = merge(merge(a, b), d);
        return res;
    }

    // pair<int,i64> kth_sum(int p, i64 k)//k 1-base, offset 0-base
    // {
    //     while(1){
    //         // push(p);
    //         i64 left = sum(t[p].ls);
    //         if(k <= left)p = t[p].ls;
    //         else if(k <= left + t[p].w)return {p, k - left - 1};
    //         else{
    //             k -= left + t[p].w;
    //             p = t[p].rs;
    //         }
    //     }
    // }

    // pair<int,i64> kth_sum(i64 k)
    // {
    //     return kth_sum(rt, k);
    // }

    int rank(int p)// node i rank
    {
        if(!p)return -1;
        // push_path(p);
        int res = sz(t[p].ls) + 1;
        while(p != 0){
            if(t[t[p].fa].rs == p)res += sz(t[t[p].fa].ls) + 1;
            p = t[p].fa;
        }
        return res - 1;
    }

};
```

## 接口使用说明

### 基本约定

- `rt`是默认操作的序列根，空树为`0`。
- `t[0]`是空节点，`sz(0)=0`。
- `t`使用整数下标表示节点，`newNode`返回的下标可以作为稳定的`node id`保存。
- 序列下标和`rank`均为**0-based**，区间均为闭区间`[l,r]`。
- 默认状态下一个物理节点表示一个序列元素，`sz`维护物理节点数。
- `split`和`merge`会修改原树，应使用返回的根继续维护序列。

### 建树与节点接口

| 接口 | 功能 |
| --- | --- |
| `Treap()` | 创建空Treap，节点池中只包含`0`号空节点 |
| `newNode()` | 分配一个未初始化为有效序列元素的节点 |
| `newNode(val)` | 创建一个值为`val`、大小为`1`的节点并返回`node id` |
| `sz(p)` | 返回以`p`为根的物理节点数 |
| `push_back(val)` | 在默认序列末尾加入一个新元素 |

按顺序建树：

```c++
Treap<int> t;
for(auto x : a)t.push_back(x);
```

需要保存新节点编号时：

```c++
t.push_back(x);
int id = t.t.size() - 1;
```

### `split`与`merge`

```c++
pair<int,int> split(int p, int rk);
```

按0-based下标拆分：

```text
左树  = 原序列 [0,rk]
右树  = 原序列 [rk+1,n-1]
```

特别地：

```text
rk < 0      -> {0,p}
rk >= n - 1 -> {p,0}
```

```c++
int merge(int l, int r);
```

按顺序连接两棵独立Treap，结果序列为：

```text
l中的全部元素 + r中的全部元素
```

`split`返回的两个根以及`merge`返回的根均满足`fa=0`。

隔离闭区间`[l,r]`：

```c++
auto [ab, c] = t.split(t.rt, r);
auto [a, b] = t.split(ab, l - 1);
// b表示[l,r]
t.rt = t.merge(t.merge(a, b), c);
```

剪切并移动一个区间时，不要调用`erase`丢弃`b`，应保留拆出的根并在目标位置重新`merge`。

### 序列操作

| 接口 | 功能 |
| --- | --- |
| `push_back(val)` | 在末尾加入`val` |
| `insert(val,rk)` | 当前实现把新节点插在原下标`rk`之后 |
| `erase(rk)` | 删除下标`rk`的一个元素 |
| `erase(l,r)` | 删除闭区间`[l,r]` |
| `query(rk)` | 返回下标`rk`处的值 |
| `rank(p)` | 返回活动节点`p`在当前序列中的0-based位置 |

当前`insert`的实际位置为：

```text
rk = -1       -> 插到最前面
0 <= rk < n   -> 插到原rk之后
rk >= n - 1   -> 插到最后面
```

该接口语义仍待后续决定，使用前应确认题目需要的是“插到位置`rk`”还是“插在`rk`之后”。

### 父指针与节点排名

| 接口 | 功能 |
| --- | --- |
| `setfa(s,p)` | 将非空节点`s`的父亲设为`p` |
| `pull(p)` | 重算`sz`并维护左右儿子的父指针 |
| `rank(p)` | 沿父指针向上计算节点位置 |

`rank(p)`只用于仍在当前活动Treap中的节点。典型用法是为排列维护`value -> node id`：

```c++
vector<int> id(n + 1);
for(int i = 0;i < n;i++){
    t.push_back(a[i]);
    id[a[i]] = t.t.size() - 1;
}

int pos = t.rank(id[x]);
```

### 可选区间翻转

默认代码不启用`rev`。需要区间翻转时，解除以下代码的注释：

- `Node::rev`；
- `push`、`push_path`、`add_tag`、`apply`；
- `merge`和`split`中的`push`；
- `rank`中的`push_path`。

启用后：

```c++
t.apply(l, r);
```

翻转闭区间`[l,r]`。如果lazy会影响左右儿子方向，调用`rank`前必须通过`push_path`把根到目标节点的标记依次下传。

### 可选聚合值二分

默认代码不启用`w/sum`。需要一个物理节点代表多个逻辑元素时，解除以下代码的注释：

- `Node::w`和`Node::sum`；
- `newNode(val)`中的默认权重初始化；
- `newNode(val,w)`；
- `sum(p)`；
- `pull`中的`sum`维护；
- 两个`kth_sum`重载。

此时：

```text
sz  = 子树物理节点数
w   = 当前节点代表的逻辑元素数
sum = 子树代表的逻辑元素总数
```

普通节点默认`w=1`。压缩区间节点可以使用：

```c++
int p = t.newNode(value, weight);
```

```c++
pair<int,i64> kth_sum(int p, i64 k);
pair<int,i64> kth_sum(i64 k);
```

`k`为1-based逻辑位置，返回：

```text
first  = 命中的node id
second = 在该节点内部的0-based偏移
```

例如节点值保存连续区间`[l,r]`时：

```c++
auto [p, offset] = t.kth_sum(k);
int value = t.t[p].val.l + offset;
```

如果同时启用lazy，需要再解除`kth_sum`内部`push(p)`的注释。

### 复杂度

设物理节点数为$n$：

| 操作 | 期望复杂度 |
| --- | --- |
| `split`、`merge` | $O(\log n)$ |
| `push_back`、`insert`、`erase`、`query`、`rank` | $O(\log n)$ |
| `apply` | $O(\log n)$ |
| `kth_sum` | $O(\log n)$ |

Treap退化时上述操作最坏为$O(n)$。
