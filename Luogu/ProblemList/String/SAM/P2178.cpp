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
        array<int,M>nxt;
        Node():len{},link{},nxt{}{}
    };
    vector<Node>t;
    vector<vector<int>>ot;
    vector<int>endpos_cnt;
    vector<ll>string_dif_cnt;
    vector<ll>string_all_cnt;
    int last = 1;

    SAM(){
        init();
    }

    SAM(string& s){
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].nxt.fill(1);
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
        while(p != 0 && t[p].nxt[x] == 0){
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
            while(p != 0 && t[p].nxt[x] == q){
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

    void calc_dif_string_cnt()
    {
        string_dif_cnt.assign(t.size(),1);
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_dif_cnt[s] += string_dif_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }

    void calc_all_string_cnt()
    {
        string_all_cnt.resize(endpos_cnt.size());
        for(int i = 0;i < t.size();i++){
            string_all_cnt[i] = endpos_cnt[i];
        }
        //transform(endpos_cnt.begin(),endpos_cnt.end(),string_all_cnt.begin(),std::_Identity<int>());
        vector<int>outdeg(t.size());
        vector<vector<int>>ig(t.size());//inner dag
        queue<int>q;
        for(int i = 1;i <t.size();i++){
            outdeg[i] = M - count(t[i].nxt.begin(),t[i].nxt.end(),0);
            if(outdeg[i] == 0)q.push(i);
            for(int j = 0;j < M;j++){
                if(t[i].nxt[j] != 0){
                    ig[nxt(i,j)].push_back(i);
                }
            }
        }
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto s : ig[p]){
                string_all_cnt[s] += string_all_cnt[p];
                outdeg[s]--;
                if(outdeg[s] == 0)q.push(s);
            }
        }
        return;
    }
};

void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    reverse(s.begin(),s.end());
    SAM sam(s);
    auto& t = sam.t;
    auto& ot = sam.ot;
    int m = t.size();
    vector<int>val(n);
    for(int i = 0;i < n;i++){
        cin>>val[i];
    }
    reverse(val.begin(),val.end());
    
    constexpr ll INF = LLONG_MIN;
    vector<ll>ma(n + 1, INF);
    vector<ll>cnt(n + 1);
    constexpr int inf = 1145141919;
    
    vector<int>maval(m, -inf),manval(m, -inf);
    vector<int>sz(m);
    int p = 1;
    for(int i = 0;i < n;i++){
        p = t[p].nxt[s[i] - 'a'];
        maval[p] = max(maval[p], val[i]);
        manval[p] = max(manval[p], -val[i]);
        sz[p]++;
    }
    

    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : ot[p]){
            self(self, s);
            if(maval[p] != -inf){
                ma[t[p].len] = max(ma[t[p].len], max(1ll * maval[p] * maval[s], 1ll * manval[p] * manval[s]));
            }
            maval[p] = max(maval[p],maval[s]);
            manval[p] = max(manval[p], manval[s]);
            cnt[t[p].len] += 1ll * sz[p] * sz[s];
            sz[p] += sz[s];
        }
    };

    dfs(dfs, 1);

    for(int i = n - 1;i >= 0;i--){
        cnt[i] += cnt[i + 1];
        ma[i] = max(ma[i],ma[i + 1]);
    }

    for(int i = 0;i < n;i++){
        if(cnt[i])cout<<cnt[i]<<" "<<ma[i]<<"\n";
        else cout<<0<<" "<<0<<"\n";
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