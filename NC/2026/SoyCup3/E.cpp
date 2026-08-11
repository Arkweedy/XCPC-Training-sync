#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.08.11 17:22:57

struct SAM {
    static constexpr int M = 26;  // 字符集大小
    struct Node {
        int len;            // 该状态代表的最长字符串的长度
        int link;           // 后缀链接
        array<int, M> nxt;  // 转移边
        Node() : len{}, link{}, nxt{} {}
    };
    vector<Node> t;  // 状态节点数组
    int last = 1;    // 指向上一个完整字符串对应的状态节点

    SAM() { init(); }

    void init() {
        t.assign(2, Node());
        t[0].len = -1;  // 虚空节点，方便处理
        t[0].nxt.fill(1);
        // t[1] 是初始状态节点，代表空串""
    }

    int newNode() {
        t.push_back(Node());
        return t.size() - 1;
    }

    void extend(int x) {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while (p != 0 && t[p].nxt[x] == 0) {
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if (p == 0) {
            t[cur].link = 1;
        } else if (t[q].len == t[p].len + 1) {
            t[cur].link = q;
        } else {
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while (p != 0 && t[p].nxt[x] == q) {
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    int nxt(int p, int x) { return t[p].nxt[x]; }
    int link(int p) { return t[p].link; }
    int len(int p) { return t[p].len; }
    int size() { return t.size(); }

    static inline int num(int x) { return x - 'a'; }
    SAM(string &s) {
        init();
        build(s);
    }

    // 完整构建 SAM
    void build(string &s) {
        for (auto &c : s) {
            extend(num(c));
        }
        get_out_linktree();
    }

    // ---- 可选部分 ---- //
    vector<vector<int>> ot;  // out-link-tree, parent 树
    vector<int> endpos_size;

    // 构建 parent 树
    void get_out_linktree() {
        ot.assign(t.size(), {});
        for (int i = 2; i < t.size(); i++) {
            ot[t[i].link].push_back(i);
        }
    }

    // 计算每个状态的 endpos 集合大小
    void calc_endpos_size(string &s) {
        endpos_size.resize(t.size());
        int p = 1;
        for (auto c : s) {
            p = t[p].nxt[num(c)];
            endpos_size[p]++;
        }
        auto dfs = [&](auto &&self, int p) -> void {
            for (auto s : ot[p]) {
                self(self, s);
                endpos_size[p] += endpos_size[s];
            }
        };
        dfs(dfs, 1);
        endpos_size[1] = 1;
    }
};

vector<int> Zfunc(string s) {
    int n = s.size();
    vector<int> z(n + 1);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = max(0, min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}

constexpr int P = 998244353;

void solve()
{
    string s, pat;
    cin >> s >> pat;
    reverse(s.begin(),s.end());
    reverse(pat.begin(),pat.end());
    SAM sam(s);
    auto& t = sam.t;
    auto& g = sam.ot;
    int n = t.size();
    
    string ps = pat + '#' + s;
    //cerr << ps << endl;
    int m = pat.size();
    auto z = Zfunc(ps);
    int fir = -1;
    vector<int>maxle(s.length());
    for(int i = 0;i < s.length();i++){
        if(i >= m - 1){
            int len = z[m + 1 + i - m + 1];
            if(len >= m){
                fir = i - m + 1;
            }
        }
        maxle[i] = i - fir;
    }
    // for(int i = 0;i < s.length();i++){
    //     cerr << maxle[i] << " ";
    // }
    // cerr << endl;
    int inf = s.length();
    vector<int>cnt(n), mx(n);
    int p = 1;
    for(int i = 0;i < s.length();i++){
        p = t[p].nxt[SAM::num(s[i])];
        mx[p] = maxle[i];
    }
    vector<int>seq;
    auto dfs2 = [&](auto&&self, int p)->void
    {
        seq.push_back(p);
        for(auto s : g[p]){
            self(self, s);
        }
    };
    dfs2(dfs2, 1);
    for(int i = n - 2;i >= 0;i--){
        int x = seq[i];
        //int delta = t[x].len - t[t[x].link].len;
        mx[t[x].link] = max(mx[x] , mx[t[x].link]);
    }
    for(int i = 1;i < n;i++){
        cnt[i] = max(0, min(mx[i], t[i].len) - t[t[i].link].len);
    }
    cnt[1] = 0; // t[0].len = -1

    // for(int i = 0;i < n;i++){
    //     cerr << i << " " << t[i].link << " "<< cnt[i] << endl;
    // }

    vector<int>dp(n, 1);
    auto dfs = [&](auto&&self, int p)->void
    {
        // include
        for(auto s : g[p]){
            self(self, s);
            dp[p] = 1ll * dp[p] * dp[s] % P;
        } 
        dp[p] = (dp[p] + cnt[p]) % P;
    };

    dfs(dfs, 1);

    // for(int i = 0;i < n;i++){
    //     cerr << dp[i] << " ";
    // }
    // cerr << endl;


    int ans = dp[1] - 1;
    ans = (ans % P + P) % P;
    cout << ans << endl;
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