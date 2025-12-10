#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int ALPHA_SIZE = 26;
struct PAM
{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int dep;//length of palindrome suffix link list
        int len;//length
        int cnt;//cnt as a ps
        int fail;//id of lps
        int diff;
        int slink;
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

    void calc_cnt()
    {
        for(int i = t.size() - 1;i > 1;i--){
            t[t[i].fail].cnt += t[i].cnt;
        }
    }
};

//和932G一样的处理
//奇数串跳过，求和变取min，本质上都是维护dp状态
//维护答案的pre数组， 发现按照某个顺序更新，全等部分会全部为len = 1
//所以跳过这部分，输出答案就行。


void solve()
{
    string s, x;
    cin>>s >> x;
    string ss;
    int n = s.length();
    for(int i = 0;i < n;i++){
        ss += s[i];
        ss += x[i];
    }
    s = ss;
    //cerr<<s<<endl;
    PAM pam;
    n = s.length();
    auto& t = pam.t;
    auto& end = pam.suff;
    constexpr int inf = 1e9;
    vector<int>dp(n + 1, inf),sdp(n + 3,inf);
    vector<int>pre(n + 1, -1);
    vector<int>smin(n + 3, 1);
    dp[0] = 0;
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        int p = end;
        while(p != 1){
            sdp[p] = dp[i + 1 - t[t[p].slink].len - t[p].diff];//new
            smin[p] = i + 1 - t[t[p].slink].len - t[p].diff;
            if(t[p].fail != t[p].slink && sdp[p] > sdp[t[p].fail]){
                sdp[p] = min(sdp[p],sdp[t[p].fail]);//last
                smin[p] = smin[t[p].fail];
            }
            if(t[p].diff == 1){
                dp[i + 1] = min(dp[i + 1], sdp[p]);
                if(dp[i + 1] == sdp[p])pre[i + 1] = smin[p];
            }
            else {
                dp[i + 1] = min(dp[i + 1], sdp[p] + 1);
                if(dp[i + 1] == sdp[p] + 1)pre[i + 1] = smin[p];
            }
            p = t[p].slink;
        }
        if(i % 2 == 0)dp[i + 1] = 1e9;
    }
    if(dp[n] == inf){
        cout<<-1<<endl;
        return;
    }
    cout<<dp[n]<<endl;
    int p = n;
    while(p != 0){
        if(pre[p] / 2 + 1 != p / 2)cout<<pre[p] / 2 + 1<<" "<<p / 2<<"\n";
        p = pre[p];
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