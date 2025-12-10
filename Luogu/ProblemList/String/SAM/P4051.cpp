#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct SAM
{
    static constexpr int M = 0;//size 
    struct Node{
        int len;
        int link;
        map<int,int>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos;
    
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        t.reserve(s.length() * 2 + 10);
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        for(int i = 0;i < 256;i++){
            t[0].nxt[i] = 1;
        }
    }

    int newNode()
    {
        t.push_back(Node());
        return t.size() - 1;
    }

    static inline int num(int x)
    {
        return x;
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
            extend(c);
        }
        //get_out_linktree();
    }

    inline int nxt(int p, int x)
    {
        return t[p].nxt[x];
    }

    void calc(string &s)
    {
        ot.resize(t.size());
        endpos.resize(t.size());
        int p = 1;
        for(int i = 2;i < t.size();i++){
            ot[t[i].link].push_back(i);
        }
        for(auto ch : s){
            p = t[p].nxt[ch];
            endpos[p]++;
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                endpos[p] += endpos[s];
            }
        };
        dfs(dfs, 1);
    }
    
};

void solve()
{
    string s;
    cin>>s;
    int n = s.length();
    s = s + s;
    s.pop_back();
    SAM sam(s);
    sam.calc(s);
    auto& t = sam.t;
    auto& endpos = sam.endpos;
    int p = 0;

    // tle
    // time : n^2 - lcp
    // use DAG 
    auto dfs = [&](auto&&self, int p, int dep)->void
    {
        for(const auto &[ch,xx] : t[p].nxt){
            assert(xx != 0);
            if(dep == n - 1){
                while(endpos[t[p].nxt[ch]]--)cout<<(char)ch;
            }
            else self(self, xx, dep + 1);
        }
    };
    dfs(dfs, 1, 0);
    cout<<endl;
    //cout<<ans<<endl;
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