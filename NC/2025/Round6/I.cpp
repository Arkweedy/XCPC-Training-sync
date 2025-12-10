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

};

class seg2 //max a[i] - i
{
    int n;
    vector<int>tree;
    vector<int>lazy;
    vector<int>len;
    vector<int>left;
    
public:
    seg2(int _n)
    {
        n = _n;
        tree.resize(n * 4);
        lazy.resize(n * 4);
        len.resize(n * 4);
        build(0,n - 1,1);
    }

private:
    void build(int l, int r, int p)
    {
        if(l == r){
            len[p] = 1;
        }
        else{
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m+1,r,p*2+1);
            len[p] = len[p * 2] + len[p * 2 + 1];
            push_up(p);
        }
    }

    void push_up(int p)
    {
        tree[p] = max(tree[p * 2],tree[p * 2 + 1]);
    }

    void push_down(int p) 
    {
        lazy[p * 2] = max(lazy[p * 2],lazy[p]);
        lazy[p * 2 + 1] = max(lazy[p * 2 + 1],lazy[p] - len[p * 2]);
        tree[p * 2] = max(tree[p * 2],lazy[p]);
        tree[p * 2 + 1] = max(tree[p * 2 + 1],lazy[p] - len[p * 2]);
        lazy[p] = 0;
    }

    void range_max(int s, int t,int val, int l, int r,int p)
    {
        if(s <= l && r <= t){
            tree[p] = max(tree[p],val - (l - s));
            lazy[p] = max(lazy[p],val - (l - s));
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_max(s,t,val,l,m,p*2);
            if(t > m)range_max(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

    int range_qry(int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){
           return tree[p];
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            int res = 0;
            if(s <= m)res = max(res,range_qry(s,t,l,m,p*2));
            if(t > m)res = max(res, range_qry(s,t,m+1,r,p*2+1));
            push_up(p);
            return res;
        }
    }

public:
    void range_max(int l, int r ,int val)
    {
        range_max(l,r,val,0,n-1,1);
    }

    int range_qry(int l, int r)
    {
        return range_qry(l,r,0,n-1,1);
    }
};

class seg1
{
    int n;
    vector<int>tree;
    vector<int>lazy;
    
public:
    seg1(int _n)
    {
        n = _n;
        tree.resize(n * 4);
        lazy.resize(n * 4);
    }

private:
    void push_up(int p)
    {
        tree[p] = max(tree[p * 2],tree[p * 2 + 1]);
    }

    void push_down(int p)
    {
        lazy[p * 2] = max(lazy[p * 2],lazy[p]);
        lazy[p * 2 + 1] = max(lazy[p * 2 + 1],lazy[p]);
        tree[p * 2] = max(tree[p * 2],lazy[p]);
        tree[p * 2 + 1] = max(tree[p * 2 + 1],lazy[p]);
        lazy[p] = 0;
    }

    void range_max(int s, int t,int val, int l, int r,int p)
    {
        if(s <= l && r <= t){
            tree[p] = max(tree[p],val);
            lazy[p] = max(lazy[p],val);
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_max(s,t,val,l,m,p*2);
            if(t > m)range_max(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

    int range_qry(int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){
            return tree[p];
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            int res = 0;
            if(s <= m)res = max(res,range_qry(s,t,l,m,p*2));
            if(t > m)res = max(res, range_qry(s,t,m+1,r,p*2+1));
            push_up(p);
            return res;
        }
    }

public:
    void range_max(int l, int r ,int val)
    {
        range_max(l,r,val,0,n-1,1);
    }

    int range_qry(int l, int r)
    {
        return range_qry(l,r,0,n-1,1);
    }
};


void solve()
{
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    SAM sam(s);
    vector<array<int,3>>qry(q);
    
    for(int i = 0;i < q;i++){
        cin>>qry[i][0]>>qry[i][1];
        qry[i][0]--;
        qry[i][1]--;
        qry[i][2] = i;
    }
   
    sort(qry.begin(),qry.end());
    
    auto &link = sam.ot;
    auto &t = sam.t;
    int len = t.size();
    vector<array<int,3>>endpos(len,{1145141919,0,0});//min, max, maxlen
    int p = 1;
    for(int i = 0;i < n;i++){
        p = t[p].nxt[SAM::num(s[i])];
        endpos[p] = {i, i, 0};
    }
    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : link[p]){
            self(self, s);
            endpos[p][0] = min(endpos[p][0],endpos[s][0]);
            endpos[p][1] = max(endpos[p][1],endpos[s][1]);
        }
    };
    dfs(dfs,1);
    for(int i = 2;i < len;i++){
        endpos[i][2] = t[i].len;
    }
    sort(endpos.begin(),endpos.end());
    seg1 t1(n);
    seg2 t2(n);
    p = 0;
    vector<int>ans(q);
    for(const auto& [mi,ma,len] : endpos){
        while(p < q && qry[p][0] < mi){
            ans[qry[p][2]] = max(t1.range_qry(qry[p][1],n - 1),t2.range_qry(qry[p][1], n - 1));//seg.ans(r, n)
            p++;
        }
        t1.range_max(0,ma - len + 1,len);
        t2.range_max(ma - len + 1, ma, len);
    }
    
    for(int i = 0;i < q;i++){
        cout<<ans[i]<<"\n";
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