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

    void calc_cnt()
    {
        for(int i = t.size() - 1;i > 1;i--){
            t[t[i].fail].cnt += t[i].cnt;
        }
    }
};

constexpr int P = 19930726;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    ll n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    PAM pam(s);
    pam.calc_cnt();
    auto&t = pam.t;
    vector<int>cnt(n + 1);
    auto dfs = [&](auto&&self, int p)->void
    {
        if(t[p].len >= 0)cnt[t[p].len] += t[p].cnt;
        for(int i = 0;i < 26;i++){
            if(t[p].next[i]){
                self(self, t[p].next[i]);
            }
        }
        return;
    };

    dfs(dfs, pam.odd_root);
    int ans = 1;
    for(int i = n;i >= 0;i--){
        if(k >= cnt[i]){
            ans = 1ll * ans * power(i, cnt[i]) % P;
            k -= cnt[i];
        }
        else{
            ans = 1ll * ans * power(i, k) % P;
            k = 0;
        }
        if(k == 0)break;
    }
    if(k > 0){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
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
        solve(
    }
    return 0;
}