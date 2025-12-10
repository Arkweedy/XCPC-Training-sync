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