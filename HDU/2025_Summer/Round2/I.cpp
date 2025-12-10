#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<typename T>
class segtree
{
    int n;
    vector<T>tree;
    vector<T>arr;

public:
    segtree(vector<T>a)
    {
        n = a.size();
        arr = a;
        tree.resize(n * 4);
        build(0,n-1,1);
    }

    segtree(int n_)
    {
        n = n_;
        arr.resize(n);
        tree.resize(n * 4);
        build(0,n - 1,1);
    }

private:
    void build(int l, int r, int p)
    {
        if(l == r){
            tree[p] = arr[l];
        }
        else{
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m + 1,r,p*2+1);
            push_up(p);
        }
    }

    void push_up(int p)
    {
        tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
    }

    void add(int pos, T val, int l, int r, int p)
    {
        if(l == r){
            tree[p] += val;
        }
        else{
            int m = l + r >> 1;
            if(pos <= m)add(pos,val,l,m,p*2);
            else add(pos,val,m + 1, r, p * 2 + 1);
            push_up(p);
        }
        return;
    }

    T qry(int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){
            return tree[p];
        }
        else{
            T res = -1;
            int m = l + r >> 1;
            if(s <= m)res = max(res, qry(s,t,l,m,p*2));
            if(m < t)res = max(res,qry(s,t,m+1,r,p*2+1));
            return res;
        }
    };

public:
    void add(int pos, T val)
    {
        add(pos,val,0,n-1,1);
    }

    T qry(int l,int r)
    {
        return qry(l,r,0,n-1,1);
    }
};

void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector<int>dfn(n),rnk(n),sz(n,1),top(n),fa(n, -1),hson(n, -1),dep(n);

    auto dfs1 = [&](auto&&self, int p)->void
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
    dfs1(dfs1,0);
    int tot = 0;
    auto dfs2 = [&](auto&&self, int p)->void
    {
        dfn[p] = tot++;
        rnk[dfn[p]] = p;
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            self(self,hson[p]);
        }
        for(auto s : g[p]){
            if(s != fa[p] && s != hson[p]){
                top[s] = s;
                self(self, s);
            }
        }
    };
    dfs2(dfs2,0);
    vector<int>val(n);
    vector<int>lazyfa(n),lazyse(n);
    for(int i = 0;i < n;i++){
        val[i] = a[rnk[i]];
    }
    
    segtree<int>t(val);

    auto update = [&](int p)->void
    {
        if(top[p] != p || p == 0)return;
        if(lazyfa[fa[p]] == lazyse[p])return;
        t.add(dfn[p],lazyfa[fa[p]] - lazyse[p]);
        lazyse[p] = lazyfa[fa[p]];
    };
    
    while(q--){
        int op, x, y;
        cin>>op>>x>>y;
        if(op == 1){
            x--,y--;
            int ans = 0;
            while(top[x] != top[y]){
                if(dep[top[x]] >= dep[top[y]]){
                    update(top[x]);
                    ans = max(ans, t.qry(dfn[top[x]],dfn[x]));
                    x = fa[top[x]];
                }
                else{
                    update(top[y]);
                    ans = max(ans, t.qry(dfn[top[y]],dfn[y]));
                    y = fa[top[y]];
                }
            }
            if(dep[x] < dep[y])swap(x, y);
            update(top[x]);
            ans = max(ans, t.qry(dfn[y],dfn[x]));
            cout<<ans<<endl;
        }
        else{
            x--;
            lazyfa[x] += y;
            if(fa[x] != -1)t.add(dfn[fa[x]],y);
            if(hson[x] != -1)t.add(dfn[hson[x]],y);
        }
    }
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