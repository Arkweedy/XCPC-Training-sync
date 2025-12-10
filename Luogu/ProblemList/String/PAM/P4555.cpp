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
        int cnt;
        int len;
        int fail;
        int trans;
        Node():next{},cnt{},len{},fail{},trans{}{}
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
        return c - 'a';
    };

    bool add(char c)
    {
        s += c;
        int x = num(c);
        int cur = get_fail(suff);
        if(t[cur].next[x]){//exist
            suff = t[cur].next[x];
            return false;
        }

        int p = newNode();
        suff = p;//new longest palindrome suffix 
        t[p].len = t[cur].len + 2;
        t[cur].next[x] = p;
        if(t[p].len == 1){//trans form odd_root
            t[p].fail = even_root;//even root
            t[p].trans = even_root;
            t[p].cnt = 1;
            return true;
        }
        int f = get_fail(t[cur].fail);// find new fail begin at lps(cur)
        t[p].fail = t[f].next[x];
        int tf = get_trans(t[cur].trans, t[p].len);
        t[p].trans = t[tf].next[x];
        t[p].cnt = t[t[p].fail].cnt + 1;
        return true;
    }

    int get_fail(int p)
    {
        // if p == odd_root -> len = -1, ok
        int len = s.length() - 1;
        while(s[len] != s[len - t[p].len - 1])p = t[p].fail; 
        return p;
    }

    int get_trans(int p, int plen)
    {
        int len = s.length() - 1;
        //(t[p].len + 2) * 2 < plen
        while(t[p].len * 2 > plen - 4 || s[len] != s[len - t[p].len - 1])p = t[p].fail; 
        return p;
    }
};


void solve()
{
    int n;
    string s;
    cin>>s;
    n = s.length();
    vector<int>l(n),r(n);
    PAM pam;
    auto &t = pam.t;
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        l[i] = t[pam.suff].len;
    }
    reverse(s.begin(),s.end());
    pam.init();
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        r[n - i - 1] = t[pam.suff].len;
    }
    int ans = 0;
    for(int i = 1;i < n;i++){
        //cerr<<l[i - 1]<<" "<<r[i]<<endl;
        ans = max(ans, l[i - 1] + r[i]);
    }
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