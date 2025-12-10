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
        int trans;//id of longest palindrome suffix that leq half length
        Node():next{},dep{},len{},cnt{1},fail{},trans{}{}
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
        return c - 'A';
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
            t[p].trans = even_root;
            t[p].dep = 1;
            return true;
        }
        int f = get_fail(t[cur].fail);// find new fail begin at lps(cur)
        t[p].fail = t[f].next[x];
        int tf = get_trans(t[cur].trans, t[p].len);
        t[p].trans = t[tf].next[x];
        t[p].dep = t[t[p].fail].dep + 1;
        return true;
    }

    int get_fail(int p)
    {
        // if p == odd_root -> len = -1, ok
        int len = s.length() - 1;
        while(len - t[p].len - 1 < 0 || s[len] != s[len - t[p].len - 1])p = t[p].fail; 
        return p;
    }

    int get_trans(int p, int plen)
    {
        int len = s.length() - 1;
        //(t[p].len + 2) * 2 < plen
        while(t[p].len * 2 > plen - 4 || len - t[p].len - 1 < 0 || s[len] != s[len - t[p].len - 1])p = t[p].fail; 
        return p;
    }

    void calc_cnt()
    {
        for(int i = t.size() - 1;i > 1;i--){
            t[t[i].fail].cnt += t[i].cnt;
        }
    }
};


void solve()
{
    string s;
    cin>>s;
    PAM pam(s);
    auto&t = pam.t;
    int n = t.size();
    vector<int>dp(n);
    dp[0] = dp[1] = -1;
    for(int i = 0;i < n;i++){//not from even_root
        if(t[i].len % 2 == 1)continue;
        //cerr<<i<<" "<<dp[i]<<" "<<dp[t[i].trans]<<endl;
        dp[i] = max(dp[i], dp[t[i].trans] + t[i].len / 2 - 1);
        for(int j = 0;j < 26;j++){//dp[even_root] = -1, but 
            if(t[i].next[j])dp[t[i].next[j]] = max(dp[t[i].next[j]], dp[i] + 1);
        }
    }
    //cerr<<dp[0]<<" "<<dp[1]<<endl;
    int ans = 0; 
    for(int i = 2;i < n;i++){
        //cerr<<dp[i]<<endl;
        if(t[i].len % 2 == 0){
            ans = max(ans, dp[i]);
        }
    }
    ans = s.length() - ans;
    cout<<ans<<endl;
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