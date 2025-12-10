// BWT of circular rotations via SA on s+s
// - 排序交给 SA（O(n log n) 倍增法，字节级 0..255）
// - 附带一个轻量 SAM（可选）：把长度为 n 的子串按 slice state 去重归类（不参与排序）
// 兼容任意字符（空格、符号等）；输入为单行原串


/**********************************/
// Author : GPT5 thinking
// 仅测试SAM是否可以通过，学习用
// 
/********************************/

#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    // 倍增 O(n log n)，字符范围 0..255
    static vector<int> build(const string &s) {
        int n = (int)s.size();
        vector<int> sa(n), rnk(n), tmp(n);
        for (int i = 0; i < n; ++i) sa[i] = i, rnk[i] = (unsigned char)s[i];
        for (int k = 1;; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rnk[a] != rnk[b]) return rnk[a] < rnk[b];
                int ra = (a + k < n ? rnk[a + k] : -1);
                int rb = (b + k < n ? rnk[b + k] : -1);
                return ra < rb;
            };
            // 基数排序可把常数更小；这里用 sort 也能过
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
                tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i-1], sa[i]) ? 1 : 0);
            for (int i = 0; i < n; ++i) rnk[i] = tmp[i];
            if (rnk[sa.back()] == n-1) break; // 已唯一排名
        }
        return sa;
    }
};

struct SAM {
    struct State {
        int link = -1, len = 0;
        int next[256];
        int firstpos = -1;
        State() { memset(next, -1, sizeof next); }
    };
    vector<State> st;
    int last = 0;

    SAM(int maxlen = 0) { st.reserve(2*maxlen+5); st.push_back(State()); }

    int extend(unsigned char c, int pos) {
        int cur = (int)st.size(); st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].firstpos = pos;
        int p = last;
        for (; p != -1 && st[p].next[c] == -1; p = st[p].link) st[p].next[c] = cur;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = (int)st.size(); st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                // st[clone].firstpos = st[q].firstpos; // 继承
                for (; p != -1 && st[p].next[c] == q; p = st[p].link) st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
        return cur;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!getline(cin, s)) return 0;
    int n = (int)s.size();
    if (n == 0) { cout << "\n"; return 0; }

    // 1) 构造 t = s + s
    string t = s + s;
    int m = (int)t.size(); // 2n

    // 2) （可选）建 SAM：演示“方法 B”的 slice 归类（不用于排序）
    //    end_state[pos]：t[0..pos] 的 end 所在状态
    SAM sam(m);
    vector<int> end_state(m);
    for (int i = 0; i < m; ++i) end_state[i] = sam.extend((unsigned char)t[i], i);

    // 预处理二进制跳表：沿 suffix link 向上
    int S = (int)sam.st.size();
    int LOG = 1;
    while ((1<<LOG) <= S) ++LOG;
    vector<vector<int>> up(LOG, vector<int>(S, -1));
    for (int v = 0; v < S; ++v) up[0][v] = sam.st[v].link;
    for (int k = 1; k < LOG; ++k)
        for (int v = 0; v < S; ++v)
            up[k][v] = (up[k-1][v] == -1 ? -1 : up[k-1][ up[k-1][v] ]);

    auto slice_state = [&](int v, int needLen)->int {
        if (sam.st[v].len < needLen) return -1;
        for (int k = LOG-1; k >= 0; --k) {
            int u = up[k][v];
            if (u != -1 && sam.st[u].len >= needLen) v = u;
        }
        // 现在 sam.st[v].len >= needLen 且 sam.st[link[v]].len < needLen
        return v;
    };

    // 把所有“长度为 n 的子串”的起点归到唯一 slice state 上（仅演示）
    vector<vector<int>> bucket(S);
    for (int pos = n-1; pos <= 2*n-2; ++pos) {
        int v = end_state[pos];
        int sv = slice_state(v, n);
        if (sv == -1) continue;
        int start = pos - n + 1; // 旋转起点
        if (0 <= start && start < n) bucket[sv].push_back(start);
    }
    for (auto &vec : bucket) if (!vec.empty()) sort(vec.begin(), vec.end()); // 同串（完全相同旋转）按起点稳定输出

    // 3) 排序交给 SA：在 t = s+s 上建 SA，取 SA[i] < n 的那些起点，即为循环旋转的字典序
    vector<int> sa = SuffixArray::build(t);

    // 4) 输出 BWT：每个起点 i 的“最后一列字符”是 s[(i + n - 1) % n]
    string ans; ans.reserve(n);
    for (int p : sa) {
        if (p < n) {
            int lastCharIdx = (p + n - 1) % n;
            ans.push_back(s[lastCharIdx]);
        }
    }
    cout << ans << '\n';

    return 0;
}
