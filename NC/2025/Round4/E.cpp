#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class segtree{
    int n;
    vector<int>tree;

public:
    segtree(int n_)
    {
        n = n_;
        tree.resize(n * 4);
    }

private:
    void push_up(int p)
    {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void update(int pos, int val, int l, int r, int p)
    {
        if(l == r){
            tree[p] = val;
        }
        else{
            int m = l + r >> 1;
            if(p <= m)update(pos,val,l,m,p*2);
            else update(pos,val,m+1,r,p*2+1);
            return;
        }
    }

    int qry(int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){
            return tree[p];
        }
        else{
            int m = l + r >> 1;
            int res = 0;
            if(s <= m)res += qry(s,t,l,m,p*2);
            if(t > m)res += qry(s,t,m+1,r,p*2+1);
            return res;
        }
    };

public:
    void update(int pos, int val)
    {
        update(pos,val,0,n-1,1);
    }

    int qry(int l, int r)
    {
        return qry(l,r,0,n-1,1);
    }
};

template<typename T>
class bit //1 base
{
    int n;
    int upper;
    vector<T>tree;

    inline static const int lowbit(const int x)
    {
        return x & -x;
    }

public:
    bit(vector<T>& a)
    {
        n = a.size() - 1;
        tree = a;
        for (int i = 1; i <= n; i++) {
            if (i + lowbit(i) <= n) {
                tree[i + lowbit(i)] += tree[i];
            }
        }
        upper = n;
        if (lowbit(upper) != upper) {
            while (upper != lowbit(upper)) {
                upper -= lowbit(upper);
            }
            upper <<= 1;
        }
    }

    void add(int p, T x)
    {
        while (p <= n) {
            tree[p] += x;
            p += lowbit(p);
        }
    }

    T qry(int r)
    {
        T res = 0;
        while (r != 0) {
            res += tree[r];
            r -= lowbit(r);
        }
        return res;
    }

    T qry(int l, int r)
    {
        if (l > 0)
            return qry(r) - qry(l - 1);
        else
            return qry(r);
    }

    int findleq(T v)const //前缀和小于等于的最大位置
    {
        int p = 0;
        T sum = 0;
        for (int len = upper; len != 0; len >>= 1) {
            if (len + p <= n && sum + tree[len + p] <= v) {
                p += len;
                sum += tree[p];
            }
        }
        return p;
    }

    int findl(T v)const //严格小的最大位置
    {
        int r = upper;
        int p = 0;
        T sum = 0;
        for (int len = upper; len != 0; len >>= 1) {
            if (len + p <= n && sum + tree[len + p] < v) {
                p += len;
                sum += tree[p];
            }
        }
        return p;
    }
};

void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        a[i] = min(a[i],100);
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>fa(n, -1),sz(n, 1),dep(n),hson(n, -1),dfn(n),top(n);
    int tot = 0;
    auto dfs1 = [&](auto&&self, int p)->void //fa,sz,dep,hson
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                dep[s] = dep[p] + 1;
                self(self, s);
                sz[p] += sz[s];
                if(hson[p] == -1 || sz[hson[p]] < sz[s]){
                    hson[p] = s;
                } 
            }
        }
    };
    auto dfs2 = [&](auto&&self, int p)->void //dfn,top
    {
        dfn[p] = tot++;
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            self(self, hson[p]);
        }
        for(auto s : g[p]){
            if(s != fa[p] && s != hson[p]){
                top[s] = s;
                self(self, s);
            }
        }
        return;
    };
    int root = 0;
    dfs1(dfs1,root);
    dfs2(dfs2,root);

    auto lca = [&](int u, int v)->int
    {
        while(top[u] != top[v]){
            if(dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            }
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };

    
    vector<int>tmp(n + 4);
    bit<int>sum1(tmp),sumg2(tmp);
    int offset = 2;
    for(int i = 0;i < n;i++){
        dfn[i] += 2;
        if(a[i] == 1){
            sum1.add(dfn[i],1);
        }
        else{
            sumg2.add(dfn[i],a[i]);
        }
    }

    auto list_sum = [&](int u, int v)->int // on one list
    {
        if(dep[u] > dep[v])swap(u,v);
        return sumg2.qry(dfn[u],dfn[v]);
    };

    auto list_cnt = [&](int u, int v)->int // on one list
    {
        if(dep[u] > dep[v])swap(u,v);
        return sum1.qry(dfn[u],dfn[v]);
    };

    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int sum = 0;
            int cnt1 = 0;
            int x,y;
            cin>>x>>y;
            x--,y--;
            int u = x, v = y;
            while(top[u] != top[v]){
                if(dep[top[u]] > dep[top[v]]){
                    sum += list_sum(u,top[u]);
                    cnt1 += list_cnt(u,top[u]);
                    u = fa[top[u]];
                }
                else{
                    sum += list_sum(v,top[v]);
                    cnt1 += list_cnt(v,top[v]);
                    v = fa[top[v]];
                }
            }
            sum += list_sum(u,v);
            cnt1 += list_cnt(u,v);
            int lca = dep[u] < dep[v] ? u : v;

            if(sum > 24){
                cout<<0<<endl;
                continue;
            }
            if(cnt1 + sum - (a[x] == 1) >= 24){
                cout<<1<<endl;
                continue;
            }

            vector<int>nodes;
            vector<int>rnodes;
            u = x, v = y;
            while(x != lca){
                nodes.push_back(x);
                x = fa[x];
            }
            while(y != lca){
                rnodes.push_back(y);
                y = fa[y];
            }
            nodes.push_back(lca);
            for(int i = rnodes.size() - 1;i >= 0;i--){
                nodes.push_back(rnodes[i]);
            }

            //dp
            vector<int>dp(24 + 1);
            
            dp[a[u]] = 1;
            for(int i = 1;i < nodes.size();i++){
                vector<int>ndp(25);
                int val = a[nodes[i]];
                for(int j = 1;j <= 24;j++){
                    if(j + val <= 24){
                        ndp[j + val] |=dp[j];
                    }
                    if(j * val <= 24){
                        ndp[j * val] |= dp[j];
                    }
                }
                dp = move(ndp);
            }
            if(dp[24]){
                cout<<1<<endl;
            }
            else{
                cout<<0<<endl;
            }
        }
        else{
            int x, d;
            cin>>x>>d;
            d = min(d,100);
            x--;
            if(a[x] == d)continue;
            if(a[x] == 1){
                sum1.add(dfn[x],-1);
                sumg2.add(dfn[x],d);
                a[x] = d;
            }
            else{
                if(d == 1){
                    sum1.add(dfn[x],1);
                    sumg2.add(dfn[x],-a[x]);
                    a[x] = d;
                }
                else{
                    sumg2.add(dfn[x],d - a[x]);
                    a[x] = d;
                }
            }
        }
    }
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