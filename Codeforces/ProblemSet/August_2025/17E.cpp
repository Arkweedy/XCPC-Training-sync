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
        //array<int,ALPHA_SIZE>next;
        map<int,int>next;
        int dep;//length of palindrome suffix link list
        int len;//length
        //int cnt;//cnt as a ps
        int fail;//id of lps
        //int trans;//id of longest palindrome suffix that leq half length
        Node():next{},dep{},len{},fail{}{}
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
        if(t[cur].next.count(x)){//exist
            suff = t[cur].next[x];
            //t[suff].cnt++;
            return false;
        }

        int p = newNode();
        suff = p;//new longest palindrome suffix 
        t[p].len = t[cur].len + 2;
        t[cur].next[x] = p;
        if(t[p].len == 1){//trans form odd_root
            t[p].fail = even_root;//even root
            //t[p].trans = even_root;
            t[p].dep = 1;
            return true;
        }
        int f = get_fail(t[cur].fail);// find new fail begin at lps(cur)
        t[p].fail = t[f].next[x];
        //int tf = get_trans(t[cur].trans, t[p].len);
        //t[p].trans = t[tf].next[x];
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

    // int get_trans(int p, int plen)
    // {
    //     int len = s.length() - 1;
    //     //(t[p].len + 2) * 2 < plen
    //     while(t[p].len * 2 > plen - 4 || len - t[p].len - 1 < 0 || s[len] != s[len - t[p].len - 1])p = t[p].fail; 
    //     return p;
    // }

    // void calc_cnt()
    // {
    //     for(int i = t.size() - 1;i > 1;i--){
    //         t[t[i].fail].cnt += t[i].cnt;
    //     }
    // }
};

constexpr int P = 51123987;

void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    PAM pam;
    auto& t = pam.t;
    auto& end = pam.suff;

    //force还是太错了
    //原来是反向计数
    vector<int>l(n),r(n);
    ll sum = 0;
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        r[i] = t[end].dep;
        sum += r[i];
        sum %= P;
    }
    reverse(s.begin(),s.end());
    pam.init();
    for(int i = 0;i < n;i++){
        pam.add(s[i]);
        l[n - i - 1] = t[end].dep;
    }
    ll ans = 1ll * sum * (sum - 1) / 2;
    for(int i = 1;i < n;i++){
        r[i] += r[i - 1];
        r[i] %= P;
        ans = (ans - 1ll * r[i - 1] * l[i] % P + P) % P; 
    }
    cout<<ans<<endl;
    return;


    //force : 记录右端点，跳fail
    //应该会tle
    // vector<int>cnt(n);
    // vector<ll>diff(n + 1);//差分，记录贡献区间
    // ll ans = 0;
    // for(int i = 0;i < n;i++){
    //     pam.add(s[i]);
    //     cnt[i] = t[end].dep;
    //     int p = end;
    //     while(p != pam.even_root){
    //         diff[i + 1]--;
    //         diff[i - t[p].len + 1]++;
    //         p = t[p].fail;
    //     }
    //     ans -= 1ll * t[end].dep * (t[end].dep + 1) / 2;//self
    // }
    // for(int i = 1;i < n;i++){
    //     diff[i] += diff[i - 1];
    //     diff[i] %= P;
    // }
    
    // for(int i = 0;i < n;i++){
    //     cerr<<cnt[i]<<" "<<diff[i]<<endl;
    //     ans += diff[i] * cnt[i];
    //     ans %= P;
    // }
    // cout<<ans<<endl;
    // return;
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