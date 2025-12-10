#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

constexpr int ALPHA_SIZE = 26;
struct GSAM{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int link;
        int len;
        Node():next{},link{},len{}{}
    };

    vector<Node>t;
    static constexpr int root = 1;

    GSAM()
    {
        init();
    }

    void init()
    {
        t.assign(2,Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int NewNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int num(char c)
    {
        return c - 'a';
    }

    void insert(const string&s)
    {
        int p = root;
        for(auto c: s){
            int x = num(c);
            if(t[p].next[x] == 0){
                t[p].next[x] = NewNode();
            }
            p = t[p].next[x];
        }
        return;
    }

    int insertSAM(int last ,int x)
    {
        int cur = t[last].next[x];
        t[cur].len = t[last].len + 1;
        int p = t[last].link;
        while(p != 0 && t[p].next[x] == 0){
            t[p].next[x] = cur;
            p = t[p].link;
        }

        if(p == 0){
            t[cur].link = 1;
        }
        else{
            int q = t[p].next[x];
            if(t[p].len + 1 == t[q].len){
                t[cur].link = q;
            }
            else{
                int clone = NewNode();
                for(int i = 0;i < ALPHA_SIZE;i++){
                    t[clone].next[i] = t[t[q].next[i]].len != 0 ? t[q].next[i] : 0;
                }
                t[clone].link = t[q].link;
                t[clone].len = t[p].len + 1;
                while(p != 0 && t[p].next[x] == q){
                    t[p].next[x] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        return cur;
    }

    void build()
    {
        queue<pair<int,int>>q;
        for(int i = 0;i < ALPHA_SIZE;i++){
            if(t[root].next[i] != 0){
                q.push(make_pair(root ,i));
            }
        }
        while(!q.empty()){
            auto [la,x] = q.front();
            q.pop();
            int last = insertSAM(la,x);
            for(int i = 0;i < ALPHA_SIZE;i++){
                if(t[last].next[i] != 0){
                    q.push(make_pair(last,i));
                }
            }
        }
    }
};

class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;

public:
    DSU(int n_)
    {
        n = n_;
        fa.resize(n);
        sz.resize(n, 1);
        iota(fa.begin(),fa.end(),0);
    }

    int find(int p)
    {
        return p == fa[p] ? p : (fa[p] = find(fa[p]));
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)return false;
        if(sz[fu] < sz[fv])swap(fu,fv);
        sz[fu] += sz[fv];
        fa[fv] = fu;
        return true;
    }
};


void solve()
{
    int n;
    cin>>n;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin>>s[i];
    }
    GSAM gsam;
    for(int i = 0;i < n;i++){
        gsam.insert(s[i]);
    }
    gsam.build();
    auto&t = gsam.t;
    int m = t.size();
    vector<vector<int>>endpos(m);
    for(int i = 0;i < n;i++){
        int p = 1;
        for(auto ch : s[i]){
            p = t[p].next[ch - 'a'];
            endpos[p].push_back(i);
        }
    }
    vector<int>id(m);
    iota(id.begin(),id.end(),0);
    sort(id.begin() + 1,id.end(),[&](int i, int j)->bool
    {
        return t[i].len > t[j].len; 
    });
    DSU dsu(n);
    ll ans = 0;

    for(int i = 1;i < m;i++){
        int p = id[i];

        int y = endpos[p][0];
        for(auto x : endpos[p]){
            if(dsu.merge(x, y)){
                ans += t[p].len;
            }
        }
        endpos[t[p].link].push_back(y);
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}

