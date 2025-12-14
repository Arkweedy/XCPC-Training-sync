#include<bits/stdc++.h>

using ll = long long;
using namespace std;


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

vector<int>f;

int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

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
    
    f.assign(n,0);
    iota(f.begin(),f.end(),0);

    vector<int>d(m);
    for(int i=1;i<m;i++){
        d[t[i].link]++;

        //cout<<i<<' '<<t[i].link<<"#\n";
    }

    priority_queue<pair<int,int>>heap;
    vector<vector<int>>e(m);

    for(int i=0;i<n;i++){
        int p = 1;
        for(auto c:s[i]){
            p = t[p].next[c - 'a'];
            e[p].push_back(i);
        }
    }

    for(int i=1;i<m;i++)if(d[i] == 0)heap.push({t[i].len,i});

    ll res = 0;
    while(!heap.empty()){
        auto [len,u] = heap.top();

        heap.pop();
        for(int i=1;i<e[u].size();i++){
            int x = e[u][i], y = e[u][i - 1];
            if(find(x) != find(y)){
                res += len;
                f[find(x)] = find(y);
            }
        }
        int p = t[u].link;

        if(p){
            d[p]--;
            e[p].push_back(e[u][0]);
            if(d[p] == 0)heap.push({t[p].len,p});
        }
    }

    cout<<res<<'\n';
    
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

