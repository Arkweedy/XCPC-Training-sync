#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.08.05 15:54:23

//使用slink指针来优化转移为回文子串的dp
constexpr int ALPHA_SIZE = 26;
struct PAM
{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int dep;
        int len;
        int cnt;
        int fail;//lps
        int diff;//与lps的长度之差
        int slink;//指向第一个diff不等于自身的回文后缀
        Node():next{},dep{},len{},cnt{1},fail{},diff{},slink{}{}
    };

    static constexpr int odd_root = 0;
    static constexpr int even_root = 1;
    //odd root -> 0
    //even root -> 1

    vector<Node>t;
    int suff;
    string s;

    PAM()
    {
        init();
    }

    PAM(string &s)
    {
        init();
        for(auto ch : s){
            add(ch);
        }
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[1].diff = 1;
        suff = 1;
        s.clear();
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    constexpr int num(const char& c)noexcept
    {
        return c - 'a';
    };

    bool add(char c)
    {
        s += c;
        int x = num(c);
        int cur = get_fail(suff);
        if(t[cur].next[x]){//exist
            suff = t[cur].next[x];
            t[suff].cnt++;
            return false;
        }

        int p = newNode();
        suff = p;//new longest palindrome suffix 
        t[p].len = t[cur].len + 2;
        t[cur].next[x] = p;
        if(t[p].len == 1){//trans form odd_root
            t[p].fail = even_root;//even root
            t[p].dep = 1;
            t[p].diff = 1;
            t[p].slink = 1;//even_root
            return true;
        }
        int f = get_fail(t[cur].fail);// find new fail begin at lps(cur)
        t[p].fail = t[f].next[x];
        t[p].dep = t[t[p].fail].dep + 1;
        t[p].diff = t[p].len - t[t[p].fail].len;
        if(t[p].diff == t[t[p].fail].diff)t[p].slink = t[t[p].fail].slink;
        else t[p].slink = t[p].fail;
        return true;
    }

    int get_fail(int p)
    {
        // if p == odd_root -> len = -1, ok
        int len = s.length() - 1;
        while(len - t[p].len - 1 < 0 || s[len] != s[len - t[p].len - 1])p = t[p].fail; 
        return p;
    }

};

struct SA {
    int n;
    std::vector<int> sa, rk, lc;
    vector<vector<int>> st;
    /*
    sa[k] = 后缀排名为 k 的后缀起始位置（k = 0..n-1）
    rk[pos] = 后缀 s[pos..] 的排名（0..n-1）
    lc[i] = LCP(sa[i], sa[i+1])

    求任意两个后缀的 LCP：LCP(s[a, n], s[b, n])
    LCP(LCP(s[l], s[l + 1]) ... LCP(s[r - 1], s[r]))
    min(lc[l] ... lc[r-1]) = rmq(l, r-1)

    */
    SA(std::string s) {
        n = s.size();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        std::iota(sa.begin(), sa.end(), 0);
        std::sort(sa.begin(), sa.end(),
                  [&](int a, int b) { return s[a] < s[b]; });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        }
        int k = 1;
        std::vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; i++) {
                tmp.push_back(n - k + i);
            }
            for (auto i : sa) {
                if (i >= k) {
                    tmp.push_back(i - k);
                }
            }
            std::fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) {
                cnt[rk[i]]++;
            }
            for (int i = 1; i < n; i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            }
            std::swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                rk[sa[i]] =
                    rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] ||
                                     sa[i - 1] + k == n ||
                                     tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            }
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; i++) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n &&
                                 s[i + j] == s[sa[rk[i] - 1] + j];) {
                    j++;
                }
                lc[rk[i] - 1] = j;
            }
        }
    }

    void init_lcp()
    {
        int K = __lg(n) + 1;//注意根据题目范围调整K大小，不同范围也可以取log计算。
        st.resize(K, vector<int>(n - 1));
        st[0] = lc;
        for (int j = 0; j < K - 1; j++) {
            for (int i = 0; i + (2 << j) <= n - 1; i++) {
                st[j + 1][i] = min(st[j][i], st[j][i + (1 << j)]);
            }
        }
    }
    
    int rmq(int l, int r) {
        int k = __lg(r - l);
        return min(st[k][l], st[k][r - (1 << k)]);
    };
    int lcp(int i, int j) {
        if (i == j || i == n || j == n) {
            return min(n - i, n - j);
        }
        int a = rk[i];
        int b = rk[j];
        if (a > b) {
            swap(a, b);
        }
        return min({n - i, n - j, rmq(a, b)});
    };
};

void solve()
{
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    string sr = s;
    reverse(sr.begin(),sr.end());
    string srs = sr + "#" + s;
    SA sa(srs);
    PAM pam, rpam;
    vector<int>ps(n),rps(n);
    auto&t = pam.t;
    auto&rt = rpam.t;
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        rpam.add(s[n - i - 1]);
        ps[i] = pam.suff;
        rps[n - i - 1] = rpam.suff;
    }

    sa.init_lcp();
    auto get = [&](int l , int r)->int
    {
        if(l < 0 || r >= n)return 0;
        return sa.lcp(n - l - 1, r + n + 1);
    };

    // 每一段的前缀相同，因此前缀匹配长度应该是一个 （增大?)->不变(已经不匹配了)的形式
    // 找到这个转折点即可
    // 可能有部分匹配的情况，所以考虑len2 ？
    // 0 是为空的情况， 只检查一边就行？

    auto calcl = [&](int l, int r)->int
    {
        if(l == -1)return 0;
        int p = ps[l];
        int ans = 0;
        while(p != 0){
            int fp = t[p].slink;
            int d = t[p].diff;
            int complen = get(l - t[fp].len, r);
            int c = complen / d;
            int len1 = t[p].len - d * c, len2 = t[p].len - d * (c + 1);
            ans = max(ans, len1 + 2 * get(l - len1, r));
            if(len2 + 1 <= l)ans = max(ans, len2 + 2 * get(l - len2, r));
            p = fp;
        }
        return ans;
    };

    auto calcr = [&](int l, int r)->int
    {
        if(r == n)return 0;
        int p = rps[r];
        int ans = 0;
        while(p != 1){
            int fp = rt[p].slink;
            int d = rt[p].diff;
            int complen = get(l, r + t[fp].len);
            int c = complen / d;
            int len1 = rt[p].len - d * c, len2 = rt[p].len - d * (c + 1);
            ans = max(ans, len1 + 2 * get(l, r + len1));
            if(r + len2 <= n)ans = max(ans, len2 + 2 * get(l, r + len2));
            p = fp;
        }
        return ans;
    };

    while(q--){
        int l, r;
        cin >> l >> r;
        l -= 2;
        int ans = max(calcl(l, r), calcr(l, r));
        cout << ans << "\n";
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}