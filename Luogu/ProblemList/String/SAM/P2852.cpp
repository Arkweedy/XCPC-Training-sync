#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct SAM
{
    static constexpr int M = 26;//size 
    struct Node{
        int len;
        int link;
        map<int,int>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_cnt;
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    SAM(vector<int>& v){
        init();
        build(v);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        return x - 'a';
    }

    void extend(int x)
    {
        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;
        while(p != 0 && !t[p].nxt.count(x)){
            t[p].nxt[x] = cur;
            p = t[p].link;
        }
        int q = t[p].nxt[x];
        if(p == 0){
            t[cur].link = 1; 
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q;
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].nxt = t[q].nxt;
            t[clone].len = t[p].len + 1;
            t[cur].link = clone;
            t[q].link = clone;
            while(p != 0 && t[p].nxt.count(x) && t[p].nxt[x] == q){
                t[p].nxt[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto &c : s){
            extend(num(c));
        }
        get_out_linktree();
    }

    void build(vector<int>& v)
    {
        for(auto &c : v){
            extend(c);
        }
        get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void get_out_linktree()
    {
        ot.resize(t.size());
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
    }

    void calc_endpos_cnt(string &s)
    {
        endpos_cnt.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[num(c)];
            endpos_cnt[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_cnt[p] += endpos_cnt[s];
            }
        };
        dfs(dfs,1);
        endpos_cnt[1] = 1;
    }

    void calc_endpos_cnt(vector<int> &s)
    {
        endpos_cnt.resize(t.size());
        int p = 1;
        for(auto c:s){
            p = t[p].nxt[c];
            endpos_cnt[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos_cnt[p] += endpos_cnt[s];
            }
        };
        dfs(dfs,1);
        endpos_cnt[1] = 1;
    }

};

void solve()
{
    int n, k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    SAM sam(a);
    sam.calc_endpos_cnt(a);
    auto &t = sam.t;
    auto &ec = sam.endpos_cnt;
    int ans = 0;
    for(int i = 2;i < t.size();i++){
        if(ec[i] >= k){
            ans = max(ans,t[i].len);
        }
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