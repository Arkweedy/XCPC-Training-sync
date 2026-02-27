#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1823F.cpp Create time : 2026.02.20 22:39

// 一个期望树形dp

constexpr int P = 998244353;

using info = int;

vector<int>ls(1), rs(1);
vector<int>t(1);
vector<int>tag(1);
stack<int>rec;

struct segtree
{
    int n;
    int root;

    segtree():n(0),root(-1){}

    segtree(int n_) = delete;

    void init(int n_)
    {
        n = n_;
        root = newNode();
    }

    int newNode()
    {
        if(!rec.empty()){
            int p = rec.top();
            rec.pop();
            return p;
        }
        else{
            t.emplace_back();
            ls.emplace_back();
            rs.emplace_back();
            tag.emplace_back(1);
            return t.size() - 1;
        }
    }

    void apply(int x, int v)
    {
        apply(x, v, 0, n - 1, root);
    }

    void push(int p)
    {
        if(tag[p] != 1){
            if(ls[p]){
                t[ls[p]] = 1ll * t[ls[p]] * tag[p] % P;
                tag[ls[p]] = tag[p];
            }
            if(rs[p]){
                t[rs[p]] = 1ll * t[rs[p]] * tag[p] % P;
                tag[rs[p]] = tag[p];
            }
            tag[p] = 1;
        }
    }

    void push_up(int p)
    {
        t[p] = 0;
        if(ls[p])t[p] = (t[p] + t[ls[p]]) % P;
        if(rs[p])t[p] = (t[p] + t[rs[p]]) % P;
        return;
    }

    void recycle(int p)
    {
        t[p] = info();
        ls[p] = rs[p] = 0;
        tag[p] = 1;
        rec.push(p);
        return;
    }

    int query(int x, int l, int r, int p)
    {
        if(p == 0)return 0;
        if(l == r){
            return t[p];
        }
        int m = l + r >> 1;
        push(p);
        if(x <= m)return query(x, l, m, ls[p]);
        else return query(x, m + 1, r, rs[p]);
    }

    void apply(int x, int v, int l, int r, int p)
    {
        if(l == r){
            t[p] = v;
            return;
        }
        int m = l + r >> 1;
        push(p);
        if(x <= m){
            if(ls[p] == 0)ls[p] = newNode();
            assert(ls[p] != 0);
            apply(x, v, l, m, ls[p]);
        }
        else{
            if(rs[p] == 0)rs[p] = newNode();
            apply(x, v, m + 1, r, rs[p]);
        }
        push_up(p);
        return;
    }

    void mul(int v)
    {
        t[root] = 1ll * t[root] * v % P;
        tag[root] = 1ll * tag[root] * v % P;
        return;
    }

    void join(segtree& ot)
    {
        assert(ot.n == n);
        join(root, ot.root, 0, n - 1);
        return;
    }

    void join(int p1, int p2, int l, int r)
    {
        if(l == r){
            t[p1] = (t[p1] + t[p2]) % P;
            return;
        }
        int m = l + r >> 1;
        push(p1);
        push(p2);
        if(ls[p1] && ls[p2])join(ls[p1], ls[p2], l, m);
        else if(ls[p2])ls[p1] = ls[p2];
        if(rs[p1] && rs[p2])join(rs[p1], rs[p2], m + 1, r);
        else if(rs[p2])rs[p1] = rs[p2];
        push_up(p1);
        recycle(p2);
        return;
    }

    int query(int x)
    {
        return query(x, 0, n - 1, root);
    }

    void print(int l, int r, int p)
    {
        if(l == r){
            cerr << "[" << l << "," << t[p] << "] ";
            return;
        }
        int m = l + r >> 1;
        if(ls[p])print(l ,m , ls[p]);
        if(rs[p])print(m + 1, r, rs[p]);
        return;
    }

    void print()
    {
        cerr << "print : " << endl;
        print(0, n - 1, root);
        cerr << endl;
    }
};

void solve()
{
    int n, s, t;
    cin >> n >> s >> t;
    s--,t--;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // rooted t
    // expect : s -> v1 -> ... -> vm -> t
    // con(s) + con(v1) + ... con(vm)
    // dp(p) = ?
    // dp(p) = cnt[subtree]
    // dsu on tree ? 
    // E(p) = 1/d {p} + 1/d \sum_s E(s) + {p} + E(p)
    // -> E(p) = d{p} + \sum_s E(s)
    // ans = \sum_{s, v1, ..., vm} E(v)

    vector<int>fa(n),dep(n), key(n);
    auto dfs1 = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dep[s] = dep[p] + 1;
                self(self, s);
            }
        }
        return;
    };
    dfs1(dfs1, t);
    //key[s] = 1;
    int tmp = s;
    while(tmp != t){
        key[tmp] = 1;
        tmp = fa[tmp];
    }

    vector<segtree>dp(n);
    for(int i = 0;i < n;i++){
        dp[i].init(n);
    }
    segtree ans;
    ans.init(n);
    auto dfs2 = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                self(self, s);
                if(!key[s]){
                    dp[p].join(dp[s]);
                }
            }
        }
        dp[p].apply(p, g[p].size());
        if(key[p]){
            dp[p].mul(dep[p]);
            ans.join(dp[p]);
        }
        return;
    };
    dfs2(dfs2, t);
    ans.apply(t, 1);

    for(int i = 0;i < n;i++){
        cout << ans.query(i) << " ";
    }
    cout << endl;
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