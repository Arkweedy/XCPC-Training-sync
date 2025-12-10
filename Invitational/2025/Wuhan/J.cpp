#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.31 18:43:14

struct SAM
{
    static constexpr int M = 26;
    struct Node{
        int len;
        int link;
        array<int,M>next;
        Node():len{},link{},next{}{}
    };

    vector<Node>t;
    int last = 1;
    
    SAM()
    {
        init();
    }

    SAM(string &s)
    {
        init();
        build(s);
    }

    void init()
    {
        t.assign(2,Node());
        t[0].len = -1;
        t[0].next.fill(1);
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
        while(p != 0 && t[p].next[x] == 0){
            t[p].next[x] = cur;
            p = t[p].link;
        }
        int q = t[p].next[x];
        if(p == 0){
            t[cur].link = 1;
        }
        else if(t[q].len == t[p].len + 1){
            t[cur].link = q;
        }
        else{
            int clone = newNode();
            t[clone].link = t[q].link;
            t[clone].next = t[q].next;
            t[clone].len = t[p].len + 1;//p error to q
            t[cur].link  = clone;
            t[q].link = clone;// miss 
            while(p != 0 && t[p].next[x] == q){
                t[p].next[x] = clone;
                p = t[p].link;
            }
        }
        last = cur;
        return;
    }

    void build(string& s)
    {
        for(auto & c : s){
            extend(num(c));
        }
    }
};

void solve()
{
    string s;
    cin>>s;
    reverse(s.begin(),s.end());
    SAM sam(s);
    auto& t = sam.t;
    int m = t.size();
    vector<int>endpos(m);
    vector<int>R(s.length());
    vector<int>len(m, -1);//min unblank length
    int p = 1;
    for(int i = 0;i < s.length();i++){
        p = t[p].next[SAM::num(s[i])];
        R[i] = p;
        endpos[p]++;
    }
    
    vector<int>id(m);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(), [&](int i, int j)->bool
    {
        return t[i].len < t[j].len;
    });
    for(int i = m - 1;i > 1;i--){
        int x = id[i];
        len[i] = t[i].len;
        endpos[t[x].link] += endpos[x];
    }

    
    int le = __lg(m) + 1;
    vector<vector<int>>g(m);
    vector<vector<int>>f(m,vector<int>(le));
    for(int i = 0;i < m;i++){
        f[i][0] = t[i].link;
        g[t[i].link].push_back(i);
    }
    for(int i = 1;i < le;i++){
        for(int j = 0;j < m;j++){
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }

    auto find = [&](int l,int r)->int
    {
        int p = R[r];
        for(int i = le - 1;i >= 0;i--){
            int s = f[p][i];
            if(t[s].len >= r - l + 1)p = s;
        }
        
        return p;
    };

    ll ans = 0;
    

    auto add = [&](int p, int x)->void // x-> begin pos
    {
        ans += max(0, len[p] - x + 1);
        len[p] = min(len[p], x - 1);
        return;
    };

    
    
    auto dfs = [&](auto&&self, int p, int r)->void
    {
        if(len[p] == t[t[p].link].len)return;
        if(p != r){
            add(p, t[t[p].link].len + 1);
        }
        for(auto s : g[p]){
            self(self, s, r);
        }
        return;
    };


    int n;
    cin>>n;
    
    for(int i = 0;i < n;i++){
        int l,r;
        cin>>r>>l;
        r = s.length() - r;
        l = s.length() - l;
        int p = find(l,r);
        dfs(dfs, p, p);
        add(p, r - l + 1);
        cout<<ans<<" ";
    }
    cout<<endl;
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