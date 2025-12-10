#include<bits/stdc++.h>
#define N 100009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using namespace std;
using ll =long long ;
const ll INF =1e18;
const int mod=998244353;

constexpr int ALPHA_SIZE = 26;
struct PAM{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int fail;
        int len;
        Node():next{},fail{},len{}{};
    };
    
    static constexpr int odd_root = 0;
    static constexpr int even_root = 1;

    vector<Node>t;
    int suff;
    string s;

    PAM()
    {
        init();
    }

    PAM(string& s)
    {
        init();
        for(auto ch:s){
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
    }

    bool add(char c)
    {
        s += c;
        int x = num(c);
        int cur = get_fail(suff);
        if(t[cur].next[x]){
            suff = t[cur].next[x];
            return false;
        }

        int p = newNode();
        suff = p;
        t[p].len = t[cur].len + 2;
        t[cur].next[x] = p;
        if(t[p].len == 1){
            t[p].fail = even_root;
            return true;
        }
        int f = get_fail(t[cur].fail);
        t[p].fail = t[f].next[x];
        return true;
    }

    int get_fail(int p)
    {
        int len = s.length() - 1;
        while(len - t[p].len - 1 < 0 || s[len] != s[len - t[p].len - 1])p = t[p].fail;
        return p;
    }
};


void solve()
{
    string s;
    cin>>s;
    cerr<<"s : "<<s<<endl;
    int n = s.length();
    int ans = 0;
    for(int i = 0;i < n;i++){
        string t;
        for(int j = i;j >= max(0, 2 * i - n + 2);j--){
            t += s[j];
            t += s[i * 2 - j + 1];
        }
        cerr<<t<<endl;
        PAM pam;
        auto& end = pam.suff;
        auto& tr = pam.t;
        vector<int>ispal(t.length() + 1);
        ispal[0] = 1;
        for(int j = 0;j + 1 < t.length();){
            pam.add(t[j]);
            pam.add(t[j + 1]);
            j += 2;
            //cerr<<"pre : "<<j - tr[end].len<<endl;
            if(ispal[j - tr[end].len]){
                ispal[j] = 1;
                ans++;
            }
        }
    }
    cout<<ans<<endl;
    return;

}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    cin>>tt;
    while(tt--) solve();
    return 0;
}