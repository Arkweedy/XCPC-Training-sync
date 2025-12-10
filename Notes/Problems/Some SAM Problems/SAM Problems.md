# 一些后缀自动机问题

## [2025HDU多校 Round 1 1004 串串](https://acm.hdu.edu.cn/contest/problem?cid=1172&pid=1004)

### 大概题意
给出 $n$ 个字符串$s_1,s_2,...s_n$,需要选出一个至少在两个$s$中出现的子串 $t$ ,设 $t$ 在 $s_i$ 中出现的位置是 $L_i$(1base,没出现记为0),最大化下面的和式：  
$$ |t|\times\sum_{i = 1}^m L_i$$
$n \leq 50, \sum |s_i| \leq 10^6$  

### 分析
需要维护多个串的子串信息,并且需要看是否是共同子串，于是考虑使用广义后缀自动机。  
观察到我们要最大化的和式是和左端点相关的，当 $t$ 长度增大的时候，端点左移,总和有减小的趋势,不好确定最优状态。  
有一个trick：将所有串取反，于是这个时候要求的就是  
$$|t|\times\sum_{i = 1}^n R_i$$
其中 $R$ 代表反串中子串的右端点出现位置。  
这个时候什么时候最优是很显然的，对于一个endpos集合，取最长的那个即可。  
于是我们可以对所有反串建立广义后缀自动机，遍历每个串的前缀序列打上标记(可以用一个ull状压一下)，记录出现位置的最大值(注意要对应到原串上,$R_i = |s_i| - len$),然后做一个DAG上的遍历来确定哪些串包含这个节点对应的子串集，出现位置的最大 $R_i$ 是多少。最后遍历广义后缀机的所有节点对答案取max即可,出现串不足两个的要跳过。  

实现代码：  
```c++
#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int MAXN = 2300000;  // 双倍字符串长度  
constexpr int CHAR_NUM = 26;   // 字符集个数，注意修改下方的 (-'a')

struct exSAM {
    int len[MAXN];             // 节点长度
    int link[MAXN];            // 后缀链接，link
    int next[MAXN][CHAR_NUM];  // 转移
    int tot;                   // 节点总数：[0, tot)

    void init() {  // 初始化函数
        tot = 1;
        link[0] = -1;
    }

    void clear()
    {
        memset(len,0,tot*sizeof(int));
        memset(link,0,tot*sizeof(int));
        memset(next,0,tot*CHAR_NUM*sizeof(int));
    }

    int insertSAM(int last, int c) {  // last 为父 c 为子
        int cur = next[last][c];
        if (len[cur]) return cur;
        len[cur] = len[last] + 1;
        int p = link[last];
        while (p != -1) {
            if (!next[p][c])
                next[p][c] = cur;
            else
                break;
            p = link[p];
        }
        if (p == -1) {
            link[cur] = 0;
            return cur;
        }
        int q = next[p][c];
        if (len[p] + 1 == len[q]) {
            link[cur] = q;
            return cur;
        }
        int clone = tot++;
        for (int i = 0; i < CHAR_NUM; ++i)
            next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
        len[clone] = len[p] + 1;
        while (p != -1 && next[p][c] == q) {
            next[p][c] = clone;
            p = link[p];
        }
        link[clone] = link[q];
        link[cur] = clone;
        link[q] = clone;
        return cur;
    }

    int insertTrie(int cur, int c) {
        if (next[cur][c]) return next[cur][c];  // 已有该节点 直接返回
        return next[cur][c] = tot++;            // 无该节点 建立节点
    }

    void insert(const string& s) {
        int root = 0;
        for (auto ch : s) root = insertTrie(root, ch - 'a');
    }

    void insert(const char* s, int n) {
        int root = 0;
        for (int i = 0; i < n; ++i)
            root =
            insertTrie(root, s[i] - 'a');  // 一边插入一边更改所插入新节点的父节点
    }

    void build() {
        queue<pair<int, int>> q;
        for (int i = 0; i < 26; ++i)
            if (next[0][i]) q.push({ i, 0 });
        while (!q.empty()) {  // 广搜遍历
            auto item = q.front();
            q.pop();
            auto last = insertSAM(item.second, item.first);
            for (int i = 0; i < 26; ++i)
                if (next[last][i]) q.push({ i, last });
        }
    }
}sam;

constexpr int N = 50;

void solve()
{
    cerr<<sizeof(int)<<endl;
    int n;
    cin >> n;
    sam.init();
    vector<string>s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        reverse(s[i].begin(), s[i].end());
        sam.insert(s[i]);
    }
    sam.build();
    vector<ull>flg(sam.tot + 1);
    vector<vector<int>> val(sam.tot + 1, vector<int>(n));
    for (int i = 0; i < n; i++) {
        int p = 0;
        int len = s[i].length();
        for (int j = 0; j < len; j++) {
            p = sam.next[p][s[i][j] - 'a'];
            flg[p] |= 1ull << i;
            val[p][i] = len - j;
        }
    }


    auto& link = sam.link;
    vector<int>indeg(sam.tot);
    for(int i = 1;i < sam.tot;i++){
        indeg[link[i]]++;
    }
    queue<int>q;
    for(int i = 1;i < sam.tot;i++){
        if(indeg[i] == 0)q.push(i);
    }
    while(!q.empty()){
        int p = q.front();
        q.pop();
        int fa = sam.link[p];
        flg[fa] |= flg[p];
        for (int j = 0; j < n; j++) {
            val[fa][j] = max(val[fa][j], val[p][j]);
        }

        indeg[fa]--;
        if(indeg[fa] == 0 && fa > 1){
            q.push(fa);
        }
    }

    ll ans = 0;
    for (int i = 1; i < sam.tot; i++) {
        ll res = 0;
        if (__popcount(flg[i]) <= 1)continue;
        for (int j = 0; j < N; j++) {
            if (flg[i] >> j & 1) {
                res += val[i][j];
            }
        }
        res *= sam.len[i];
        ans = max(ans, res);
    }

    cout << ans << endl;
    sam.clear();
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
```

## [2025牛客多校 Round 6 I  Longest Common Substring](https://ac.nowcoder.com/acm/contest/108303/I)

### 题目大意
给定一个长为 $n$ 的字符串 $s$ 和 $q$ 次询问，每次询问给定 $l,r$, 求前缀 $s[1:l]$ 和后缀 $s[r,n]$ 的最长公共子串。  
$n, q \leq 2\times 10^5$  

### 分析
因为要维护子串的信息，我们还是对 $s$ 建立后缀自动机。  
寻找前后缀 $l, r$ 的公共子串，即找一个节点,它的min endpos小于等于前缀,且max endpos 大于等于后缀。  
在SAM上维护min,max endpos是简单的，设一个节点 $p$ 的min,max endpos 为 $ma_p, mi_p$。  
如果是要最长的公共子串,对于满足条件的节点$p$,右边的子串可能取不完,最长的公共子串长度容易推出来： $\min(len_p, ma_p - r + 1)$  
那么对于一个询问$\{l,r\}$ ,我们可以得到它的答案：  
$$\max_{p \in SAM(s), mi_p \leq l} \min(len_p, ma_p - r + 1)$$  
在线回答好像不太能，考虑使用离线做法。  
对于一个询问 $\{l,r\}$,只用考虑所有$mi \leq l$ 的节点的贡献。所以我们可以按照 $l$ 排序询问离线处理,不断加入后缀自动机的节点，维护后缀端点 为 $r$ 的答案，当加入完所有 $len_p \leq l$ 的节点后，回答询问 $\{l, r\}$  
显然维护信息，回答查询需要区间操作，尝试使用线段树维护。  
以后缀端点 $r$ 作为线段树维护的下标，贡献的式子并不利于直接维护，尝试将 $\min$ 操作拆开，分成两部分分别维护。原来$\min$式对于 $r$ 的图是一个折线，对于$len_p \leq ma_p - r + 1$, 即 $r \leq ma_p - len_p + 1$ 部分，贡献是常数 $len_p$, 对于 $r \geq ma_p - len_p + 1$ 部分，贡献是一段斜率为$ -1 $ 的直线。  
常数段是好维护的，斜率段可以通过插入 $ma_p + 1$,线段树维护 $ma_p - i + 1$的最大值即可，这个的push_up ,push_down并不难实现。
最后的实现代码如下：  
```c++
#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct SAM
{
    static constexpr int M = 26;//size 
    struct Node{
        int len;
        int link;
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_cnt;
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].nxt.fill(1);
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        return x - 'a';
    }

    void extend(int x)
    {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && t[p].nxt[x] == 0){
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if(p == 0){
            t[cur].link = 1; 
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q;
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while(p != 0 && t[p].nxt[x] == q){
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto &c : s){
            extend(num(c));
        }
        get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void get_out_linktree()
    {
        ot.resize(t.size());
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
    }

    void calc_endpos_cnt(string &s)
    {
        endpos_cnt.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_cnt[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_cnt[p] += endpos_cnt[s];
            }
        };
        dfs(dfs,1);
        endpos_cnt[1] = 1;
    }

};

class seg2 //max a[i] - i
{
    int n;
    vector<int>tree;
    vector<int>lazy;
    vector<int>len;
    vector<int>left;
    
public:
    seg2(int _n)
    {
        n = _n;
        tree.resize(n * 4);
        lazy.resize(n * 4);
        len.resize(n * 4);
        build(0,n - 1,1);
    }

private:
    void build(int l, int r, int p)
    {
        if(l == r){
            len[p] = 1;
        }
        else{
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m+1,r,p*2+1);
            len[p] = len[p * 2] + len[p * 2 + 1];
            push_up(p);
        }
    }

    void push_up(int p)
    {
        tree[p] = max(tree[p * 2],tree[p * 2 + 1]);
    }

    void push_down(int p) 
    {
        lazy[p * 2] = max(lazy[p * 2],lazy[p]);
        lazy[p * 2 + 1] = max(lazy[p * 2 + 1],lazy[p] - len[p * 2]);
        tree[p * 2] = max(tree[p * 2],lazy[p]);
        tree[p * 2 + 1] = max(tree[p * 2 + 1],lazy[p] - len[p * 2]);
        lazy[p] = 0;
    }

    void range_max(int s, int t,int val, int l, int r,int p)
    {
        if(s <= l && r <= t){
            tree[p] = max(tree[p],val - (l - s));
            lazy[p] = max(lazy[p],val - (l - s));
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_max(s,t,val,l,m,p*2);
            if(t > m)range_max(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

    int range_qry(int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){
           return tree[p];
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            int res = 0;
            if(s <= m)res = max(res,range_qry(s,t,l,m,p*2));
            if(t > m)res = max(res, range_qry(s,t,m+1,r,p*2+1));
            push_up(p);
            return res;
        }
    }

public:
    void range_max(int l, int r ,int val)
    {
        range_max(l,r,val,0,n-1,1);
    }

    int range_qry(int l, int r)
    {
        return range_qry(l,r,0,n-1,1);
    }
};

class seg1
{
    int n;
    vector<int>tree;
    vector<int>lazy;
    
public:
    seg1(int _n)
    {
        n = _n;
        tree.resize(n * 4);
        lazy.resize(n * 4);
    }

private:
    void push_up(int p)
    {
        tree[p] = max(tree[p * 2],tree[p * 2 + 1]);
    }

    void push_down(int p)
    {
        lazy[p * 2] = max(lazy[p * 2],lazy[p]);
        lazy[p * 2 + 1] = max(lazy[p * 2 + 1],lazy[p]);
        tree[p * 2] = max(tree[p * 2],lazy[p]);
        tree[p * 2 + 1] = max(tree[p * 2 + 1],lazy[p]);
        lazy[p] = 0;
    }

    void range_max(int s, int t,int val, int l, int r,int p)
    {
        if(s <= l && r <= t){
            tree[p] = max(tree[p],val);
            lazy[p] = max(lazy[p],val);
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_max(s,t,val,l,m,p*2);
            if(t > m)range_max(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

    int range_qry(int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){
            return tree[p];
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            int res = 0;
            if(s <= m)res = max(res,range_qry(s,t,l,m,p*2));
            if(t > m)res = max(res, range_qry(s,t,m+1,r,p*2+1));
            push_up(p);
            return res;
        }
    }

public:
    void range_max(int l, int r ,int val)
    {
        range_max(l,r,val,0,n-1,1);
    }

    int range_qry(int l, int r)
    {
        return range_qry(l,r,0,n-1,1);
    }
};


void solve()
{
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    SAM sam(s);
    vector<array<int,3>>qry(q);
    
    for(int i = 0;i < q;i++){
        cin>>qry[i][0]>>qry[i][1];
        qry[i][0]--;
        qry[i][1]--;
        qry[i][2] = i;
    }
   
    sort(qry.begin(),qry.end());
    
    auto &link = sam.ot;
    auto &t = sam.t;
    int len = t.size();
    vector<array<int,3>>endpos(len,{1145141919,0,0});//min, max, maxlen
    int p = 1;
    for(int i = 0;i < n;i++){
        p = t[p].nxt[SAM::num(s[i])];
        endpos[p] = {i, i, 0};
    }
    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : link[p]){
            self(self, s);
            endpos[p][0] = min(endpos[p][0],endpos[s][0]);
            endpos[p][1] = max(endpos[p][1],endpos[s][1]);
        }
    };
    dfs(dfs,1);
    for(int i = 2;i < len;i++){
        endpos[i][2] = t[i].len;
    }
    sort(endpos.begin(),endpos.end());
    seg1 t1(n);
    seg2 t2(n);
    p = 0;
    vector<int>ans(q);
    for(const auto& [mi,ma,len] : endpos){
        while(p < q && qry[p][0] < mi){
            ans[qry[p][2]] = 
            max(
            t1.range_qry(qry[p][1],qry[p][1]),
            t2.range_qry(qry[p][1], qry[p][1])
            );//seg.ans(r, n)
            p++;
        }
        t1.range_max(0,ma - len + 1,len);
        t2.range_max(ma - len + 1, ma, len);
    }
    
    for(int i = 0;i < q;i++){
        cout<<ans[i]<<"\n";
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
```

## [P4248 差异](https://www.luogu.com.cn/problem/P4248)

### 大概题意
给定一个长度为 $n$ 的字符串 $S$，令 $T_i$ 表示它从第 $i$ 个字符开始的后缀。求  

$$\displaystyle \sum_{1\leqslant i<j\leqslant n}\operatorname{len}(T_i)+\operatorname{len}(T_j)-2\times\operatorname{lcp}(T_i,T_j)$$
其中，$\text{len}(a)$ 表示字符串 $a$ 的长度，$\text{lcp}(a,b)$ 表示字符串 $a$ 和字符串 $b$ 的最长公共前缀。  
$2\le n\le 5\times 10^5$，且 $S$ 中均为小写字母。  

即求所有后缀对的$\operatorname{lcp}$长度之和。  

### 分析
限制$(i,j)$不同且有序不太好算，可以去掉这两个限制后容斥一下。  
$\operatorname{len}$ 的和是好算的。所以我们计算 $\sum_{1\leqslant i,j\leqslant n}\operatorname{lcp}(T_i,T_j)$,去掉 $i,j$ 相同的部分，取一半即可。  
现在的问题是怎么计算   
$$\sum_{1\leqslant i,j\leqslant n}\operatorname{lcp}(T_i,T_j)$$
在后缀自动机上，求两个后缀的 $\operatorname{lcp}$ 并不好求，但是我们可以求两个前缀的  $\operatorname{lcs}$
于是我们将原串取反，问题成了求  
$$\sum_{1\leqslant i,j\leqslant n}\operatorname{lcs}(T_i,T_j)$$
其中，$T_i$ 表示反串中长为 $i$ 的前缀。这两个问题是等价的。  
考虑两个前缀的 $\operatorname{lcs}$ 在后缀自动机上的表现,显然是它们在后缀连接树上的$\operatorname{lca}$。于是我们标记所以前缀对应的后缀自动机节点，做一个树形dp来确定每个节点是多少个前缀对的 $\operatorname{lcs}$ 即可。  
前缀对数量的计算是简单的,在后缀连接树上：  
$$cnt[p] = \left(\sum_{s\in son(p)} endpos[s]\right)^2 - \sum_{s \in son(p)} endpos[s]^2$$
其中 $endpos$ 表示节点的endpos集合的大小。  
为什么是使用endpos集合的大小呢？实际上endpos的含义除了每个节点代表的子串的出现不同位置数，也代表着这个节点代表的子串作为串的前缀 的后缀的个数
(甚至其实可以说这两种定义是等价的，甚至求endpos的方法就是这样来的!)  
于是我们就可以轻松求出这题的答案了。  
以及一个不算意外，但又很有意思的结论：  
>  **一个字符串的所有后缀对的 lcp 长度之和 等于所有前缀对 lcs 的长度之和**  

所以说其实我们不需要翻转字符串，仍然可以得到正确答案。  
其实从后缀树的角度可以理解这件事情：  
后缀树上两个节点的 $\operatorname{lca}$，是两个后缀的 $\operatorname{lcp}$, 而后缀树也同时是反串的SAM的后缀连接树。  
对前缀对求 $\operatorname{lca}$ 和对后缀对求 $\operatorname{lcp}$,似乎总和都是由相同的子串贡献的？所以答案一样。

实现代码：  
```c++
#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct SAM
{
    static constexpr int M = 26;//size 
    struct Node{
        int len;
        int link;
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<ll>endpos_cnt;
    vector<ll>string_dif_cnt;
    vector<ll>string_all_cnt;
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].nxt.fill(1);
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        return x - 'a';
    }

    void extend(int x)
    {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && t[p].nxt[x] == 0){
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if(p == 0){
            t[cur].link = 1; 
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q; 
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while(p != 0 && t[p].nxt[x] == q){
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto &c : s){
            extend(num(c));
        }
        get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void get_out_linktree()
    {
        ot.resize(t.size());
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
    }

    void calc_endpos_cnt(string &s)
    {
        endpos_cnt.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_cnt[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_cnt[p] += endpos_cnt[s];
            }
        };
        dfs(dfs,1);
        endpos_cnt[1] = 1;
    }

    void calc_dif_string_cnt()
    {
        string_dif_cnt.assign(t.size(),1);
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_dif_cnt[s] += string_dif_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }

    void calc_all_string_cnt()
    {
        string_all_cnt.resize(endpos_cnt.size());
        for(int i = 0;i < t.size();i++){
            string_all_cnt[i] = endpos_cnt[i];
        }
        //transform(endpos_cnt.begin(),endpos_cnt.end(),string_all_cnt.begin(),std::_Identity<int>());
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_all_cnt[s] += string_all_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }
};

void solve()
{
    string s;
    cin>>s;
    //reverse(s.begin(),s.end());
    SAM sam(s);
    ll n = s.length();
    ll ans = n * (n + 1) * n;
    sam.calc_endpos_cnt(s);
    auto &t = sam.t;
    auto &ot = sam.ot;
    auto &ecnt = sam.endpos_cnt;
    ll all = 0;
    ll del = 0;
    vector<int>isprefix(t.size());
    vector<ll>cnt(t.size());
    for(int i = 2;i < t.size();i++){
        cnt[i] = ecnt[i] * ecnt[i];
    }
    for(int i = 2;i < t.size();i++){
        cnt[t[i].link] -= ecnt[i] * ecnt[i];
    }
    for(int i = 2;i < t.size();i++){
        ans -= cnt[i] * t[i].len * 2;
    }
    ans /= 2;
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}
```

## [2025 牛客多校 Round 5 B Extra Training](https://ac.nowcoder.com/acm/contest/108302/B)  

### 大概题意
给定一个字符串 $S$ , 每次可以选择 $S$ 的一个子串(可以是空串)拼接, 问 $k$ 次拼接可以形成多少种不同的串。     
范围： $n \leq 5 \times 10^5, k \leq 10^9$    

### 分析
显然不能够直接拼接 $10^9$ 次，得考虑使用矩阵快速幂加速递推。  
我们需要对拼接出来的字符串去重，所以我们可以选择一个字符串最早被拼出来的那一次进行计算。
如果我们要计算一个字符串被最早拼出来的一次，我们必须要对选择来拼接的子串做出限制以达到我们的目标。   
一个好理解的结论 ： 如果一个子串 $t$ 加上一个字符 $c$ 后仍然属于原串的子串，那么显然这不会是一个 "最快的" 方案。   
那么我们如果做出如下限制: 对于我们在串后拼接的子串，只能选择符合"最快"方案的，即如果我们当前拼接出来的串中，最后一个子串为 $t$， 且定义 $t$ 的接受字符集 $\Sigma_t = \{c \mid t + c \notin S\}$, 那么我们只能选择以 $\Sigma_t$ 中字符开头的子串进行拼接。   
再考虑设置一个结束状态 $\emptyset$，任何字符开头的子串可以后接 结束状态 $\emptyset$ 。   
这个结束状态可以理解为空串，开始拼接空串即代表构造结束。   
于是我们拼接一个子串 $t$ 只受到开头字符的限制，并在拼接后变成 $t$ 的限制。   
在后缀自动机上，我们可以在DAG上得到每个endpos集合的第一个字符的集合，也可以得到它们后接哪些字符可以转移，哪些不能。   
于是我们设计如下的递推状态转移：   
$dp_{i, j}$ 表示当前拼接出来的串中，以 $i$ 字符开头， 且可以后接 $j$ 字符的串的个数。其中也包含结束状态字符。   
$tr_{i,j}$ 表示 $S$ 中以 $i$ 字符开头，且可以后接 $j$ 字符的子串的个数。   
滚动递推，有：   
$$ndp_{i,j} = \sum_{k \in \Sigma} dp_{i,k} \times tr_{k, j}$$   
完全就是矩阵乘法的形式!   
于是我们可以将这个转移写成矩阵递推的形式,使用矩阵快速幂优化。   
初始的dp状态是一个初始字符 $\pi$，可以后接任意字符开头的串。所以是 $dp_{\pi,c \in \Sigma} = 1$   

下面我们想办法利用后缀自动机求出转移矩阵 $tr$   
特殊的，我们在结束状态只能拼接一个空串，此时结束状态仍然保持，所以有 $tr_{\emptyset,\emptyset} = 1$   
一般的，我们要求出所有以 $i$ 字符开头，且可以后接 $j$ 字符的子串的个数。   
如果直接**先序遍历**SAM的DAG,在转移的时候记录每个节点以每个字符开头的子串数，计数是 $O(n \Sigma)$ 的，因为后缀自动机的转移边只有 $O(n)$ 条。   
然而，后续统计是麻烦的。对于每个不能转移的边，我们得花费 $O(\Sigma)$ 的时间将贡献加到 $tr$ 上，这是 $O(n \Sigma^2)$ 的。而这个复杂度的代码将会超时。(虽然哥哥的代码卡过去了)   
可能的代码如下：   
```c++
    vector<array<int,V>>cnt(m);
    //cnt[i][j] ->node is i, first char is j  cnt
    vector<int>indeg(m);//tmp for topo sort
    for(int i = 1;i < m;i++){
        for(int j = 0;j < M;j++){
            if(t[i].nxt[j] != 0){
                indeg[t[i].nxt[j]]++;
            }
        }
    }
    // init first char from root, when tranverse, first is keep 
    for(int i = 0;i < M;i++){
        if(t[1].nxt[i] != 0)
            cnt[t[1].nxt[i]][i]++;
    }
    queue<int>q;
    q.push(1);
    while(!q.empty()){//topo order tranverse
        int p = q.front();
        q.pop();
        for(int i = 0;i < M;i++){
            
            int s = t[p].nxt[i];//first cases
            if(s){
                cnt[s] += cnt[p];
                indeg[s]--;
                if(indeg[s] == 0)q.push(s);
            }
            else{
                for(int j = 0;j < M;j++){//O(nV^2)
                    tr[j][i] += cnt[p][j];
                }
            }
        }
        for(int j = 0;j < M;j++){
            tr[j][V - 1] += cnt[p][j];
        }
    }
    print(tr);
```
这是因为我们预处理以每个字符开头的串后，将其**均摊到每个节点上去计算**了。也就是我们是**通过DAG转移开头字符信息**，**在节点上计算可否后接字符信息**。   
但是如果我们在DAG上转移可否后接字符信息，在节点上计算开头字符信息，情况是否会变得不一样呢？   
使用这种做法，我们使用**后序遍历**来遍历DAG,计算是否可以转移时，如果不能，我们$O(1)$加到该节点的转移计数数组上，而这大概有$O(n \Sigma)$ 次。
然后，我们通过转移边，将其计数信息 $O(\Sigma)$ 转移到父节点上(当然可能有多个，这代表前接一个字符)，而转移边有$O(n)$条，这部分的复杂度也是 $O(n \Sigma)$的。   
最后，我们只需要通过根节点访问以每个字符开头的"根节点"，遍历可以后接的字符计数数组，加入到 $tr$ 中，这部分时间复杂度是 $O(\Sigma ^2)$。
在这种做法下，时间复杂度被优化到了 $O(n \Sigma)$,而我们仅仅是换了一种遍历和统计的方式，就将 $O(n \Sigma^2)$的复杂度拆分到 $O(n \Sigma)$ 和 $O(\Sigma^2)$ 上去。   
这种改变统计方式从而改变时间复杂度的trick也是我攻克这道题的卡点之一，其根源大概是SAM的DAG中，可以转移的边有$O(n)$条，不能的有$O(n \Sigma)$ 条，而我们的计数操作有 $O(1)$ 和 $O(\Sigma)$ 两种？而转移起来均为 $O(\Sigma)$, 所以要正确搭配计数转移和转移边？（感觉可以分析出来这里的不同，但是还说不上透彻，对这里产生差异的根源不够清楚）   
于是我们可以得到正确时间复杂度计算$tr$的代码：   
```c++
    matrix tr;
    tr[V - 1][V - 1] = 1;

    //tr[i][j] -> begin is i, can link j
    vector<array<ll,V>>cnt(m);
    //cnt[i][j], begin from node i,  can link char c 'cnt
    //attention the difference 
    vector<int>vs(m);
    auto dfs = [&](auto&&self, int p)->void
    {
        if(vs[p])return;
        vs[p] = true;
        cnt[p][V - 1] = 1;//initial 
        for(int i = 0;i < M;i++){
            int s = t[p].nxt[i];
            if(s){                
                self(self, s);
                //scnt[p] += scnt[s];
                cnt[p] += cnt[s]; //recalc
                //cnt[p][i] += scnt[s];
            }
            else{
                cnt[p][i]++;
            }
        }
    };
    dfs(dfs, 1);


    for(int i = 0;i < M;i++){
        int p = t[1].nxt[i];
        if(p){
            for(int j = 0;j < V;j++){
                tr[i][j] = cnt[p][j];
            }
        }
    }
```

得到了转移矩阵 $tr$ ,我们做一遍矩阵快速幂就好。   
这部分时间复杂度 $O(\Sigma^3 \log k)$   

统计答案的部分，我们直接计算从初始字符开始转移，以可以转移到结束状态的串的个数即可。   
为什么是结束状态？   
结束状态是一个"吸收态",代表着所有的合法转移的个数(合法转移都可以转移到结束态),而如果直接计算转移到各个字符结尾的串的加和，显然会重复计数。   
初始状态字符 $\pi$ 的设置是随意的,可以是不同的，只需要每个字符可以被转移到，仅用于计数，可以单开一维，甚至可以取结束状态。   
于是可以全部设置成同一个字符 $\pi$ 转移到全部字符，最后查询 $\pi$ 到终止状态的方案数即可。   
所以，将初始状态初始化为单位矩阵，最后计算每个字符转移到终止状态的和也是对的。   
甚至可以随便设置，只需要保证每个字符被转移到一次即可，最后不重不漏地统计就行。    
所以你这样初始化都没问题：
```c++
    //matrix res = get_diag(1); // ok
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    const int pi = g() % V;
    vector<int>row(V),col(V);
    iota(row.begin(),row.end(),0);
    iota(col.begin(),col.end(),0);
    shuffle(row.begin(),row.end(),g);
    shuffle(col.begin(),col.end(),g);
    matrix res{};
    for(int i = 0;i < V;i++){
        //res[pi][i] = 1;//correct ,calc can use res[pi][V-1] as ans
        res[row[i]][col[i]] = 1; //correct
        //res[g() % V][col[i]] = 1; //correct
        //res[row[i]][g() % V] = 1; //wrong,can not assure col
    }

    while(k){
        if(k & 1)res = res * tr;
        tr = tr * tr;
        k >>= 1;
    }

    Z ans = 0;
    //ans = res[pi][V - 1];
    for(int i = 0;i < V;i++){
        ans += res[i][V - 1];
    }
    cout<<ans<<endl;
    return;
```

完整代码如下   
```c++
#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int M = 52;//size 
constexpr int V = M + 1;
struct SAM
{
    struct Node{
        int len;
        int link;
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_size;
    
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].nxt.fill(1);
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        if(islower(x))return x - 'a';
        else return x - 'A' + 26;
        //return x - 'a';
    }

    void extend(int x)
    {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && t[p].nxt[x] == 0){
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if(p == 0){
            t[cur].link = 1; 
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q; 
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while(p != 0 && t[p].nxt[x] == q){
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto &c : s){
            extend(num(c));
        }
        //get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void get_out_linktree()
    {
        ot.resize(t.size());
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
    }

    void calc_endpos_size(string &s)
    {
        endpos_size.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_size[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_size[p] += endpos_size[s];
            }
        };
        dfs(dfs,1);
        endpos_size[1] = 1;
    }
};

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
//template<>
//int MInt<0>::Mod = 998244353;
//int MInt<0>::Mod = 1000000007;
constexpr int P = 998244353;
//constexpr int P = 1000000007;
using Z = MInt<P>;


using matrix = array<array<Z,V>,V>;

matrix operator*(const matrix& lhs, const matrix& rhs)
{
    matrix res{};
    for(int i = 0;i < V;i++){
        for(int j = 0;j < V;j++){
            for(int k = 0;k < V;k++){
                res[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return res;
}

matrix get_diag(int x)
{
    matrix m;
    for(int i = 0;i < V;i++){
        m[i][i] = x;
    }
    return m;
}

template<typename T>
array<T, V> operator+(const array<T,V>&lhs, const array<T,V>&rhs)
{
    array<T,V>res{};
    for(int i = 0;i < V;i++){
        res[i] = lhs[i] + rhs[i];
    }
    return res;
}

template<typename T>
array<T, V>& operator+=(array<T,V>&lhs, const array<T,V>&rhs)
{
    for(int i = 0;i < V;i++){
        lhs[i] += rhs[i];
    }
    return lhs;
}

void print(matrix m)
{
    for(int i = 0;i < V;i++){
        for(int j = 0;j < V;j++){
            cerr<<m[i][j]<<" ";
        }
        cerr<<endl;
    }
    cerr<<endl;
}

// 3 0 3 
// 2 1 2 
// 0 0 1 

// 3 1 3 
// 2 1 2 
// 0 0 1 

void solve()
{
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    SAM sam(s);
    auto &t = sam.t;
    int m = t.size();
    matrix tr;
    tr[V - 1][V - 1] = 1;

    //tr[i][j] -> begin is i, can link j ?

    //vector<ll>scnt(m, 1);
    vector<array<ll,V>>cnt(m);
    vector<int>vs(m);
    auto dfs = [&](auto&&self, int p)->void
    {
        if(vs[p])return;
        vs[p] = true;
        cnt[p][V - 1] = 1;//initial 
        for(int i = 0;i < M;i++){
            int s = t[p].nxt[i];
            if(s){                
                self(self, s);
                cnt[p] += cnt[s]; //recalc
            }
            else{
                cnt[p][i]++;// ? 
            }
        }
    };
    dfs(dfs, 1);


    for(int i = 0;i < M;i++){
        int p = t[1].nxt[i];
        if(p){
            for(int j = 0;j < V;j++){
                tr[i][j] = cnt[p][j];
            }
        }
    }

    //print(tr);

    // vector<array<int,V>>cnt(m);
    // vector<int>indeg(m);
    // for(int i = 1;i < m;i++){
    //     for(int j = 0;j < M;j++){
    //         if(t[i].nxt[j] != 0){
    //             indeg[t[i].nxt[j]]++;
    //         }
    //     }
    // }
    // for(int i = 0;i < M;i++){
    //     if(t[1].nxt[i] != 0)
    //         cnt[t[1].nxt[i]][i]++;
    // }
    // queue<int>q;
    // q.push(1);
    // while(!q.empty()){
    //     int p = q.front();
    //     q.pop();
    //     for(int i = 0;i < M;i++){
            
    //         int s = t[p].nxt[i];//first cases
    //         if(s){
    //             cnt[s] += cnt[p];
    //             indeg[s]--;
    //             if(indeg[s] == 0)q.push(s);
    //         }
    //         else{
    //             for(int j = 0;j < M;j++){//O(nV^2)
    //                 tr[j][i] += cnt[p][j];
    //             }
    //         }
    //     }
    //     for(int j = 0;j < M;j++){
    //         tr[j][V - 1] += cnt[p][j];
    //     }
    // }
    // print(tr);


    //matrix res = get_diag(1);
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    const int pi = g() % V;
    matrix res{};
    for(int i = 0;i < V;i++){
        res[pi][i] = 1;
    }

    // print(tr);
    // print(res);

    while(k){
        if(k & 1)res = res * tr;
        tr = tr * tr;
        k >>= 1;
    }

    //print(res);

    Z ans = 0;
    ans = res[pi][V - 1];
    // for(int i = 0;i < V;i++){
    //     ans += res[i][V - 1];
    //     //ans += res[V - 1][i];
    // }
    cout<<ans<<endl;
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
```

多校后缀自动机的题解先告一段落。  
后面加训字符串应该还好写ACAM,SAM,PAM各种题的题解，不过应该会少些篇幅？  












