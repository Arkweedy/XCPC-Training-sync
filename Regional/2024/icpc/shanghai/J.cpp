#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class segtree
{
    int n;
    vector<int>lazy;

public:
    segtree(int _n)
    {
        n = _n;
        lazy.resize(n * 4, -1);
    }

private:
    //void build(int p)
    void push_down(int p)
    {
        if(lazy[p] != -1){
            lazy[p * 2] = lazy[p * 2 + 1] = lazy[p];
            lazy[p] = -1;
        }
    }

    void update(int s, int t, int val, int l, int r, int p)
    {
        if(s <= l && r <= t){
            lazy[p] = val;
            return;
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            //lazy[p] = -1;
            if(s <= m)update(s,t,val,l,m,p*2);
            if(t > m)update(s,t,val,m+1,r,p*2+1);
        }
    }

    int qry(int pos, int l, int r, int p)
    {
        if(l == r){
            return lazy[p];
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            if(pos <= m) return qry(pos,l,m,p*2);
            else return qry(pos,m+1,r,p*2+1);
        }
    }

public:
    void upt(int l, int r, int val)
    {
        update(l,r,val,0,n-1,1);
    }

    int qry(int pos)
    {
        return qry(pos,0,n-1,1);
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
    int n, q;
    cin>>n>>q;
    vector<int>xl(n),xr(n),yl(n),yr(n);
    vector<int>x,y;
    for(int i = 0;i < n;i++){
        cin>>xl[i]>>yl[i]>>xr[i]>>yr[i];
        x.push_back(xl[i]);
        x.push_back(xr[i]);
        y.push_back(yl[i]);
        y.push_back(yr[i]);
    }

    sort(x.begin(),x.end());
    x.erase(unique(x.begin(),x.end()),x.end());
    sort(y.begin(),y.end());
    y.erase(unique(y.begin(),y.end()),y.end());
    int xm = x.size(), ym = y.size();
    for(int i = 0;i < n;i++){
        xl[i] = lower_bound(x.begin(),x.end(),xl[i]) - x.begin();
        xr[i] = lower_bound(x.begin(),x.end(),xr[i]) - x.begin();
        yl[i] = lower_bound(y.begin(),y.end(),yl[i]) - y.begin();
        yr[i] = lower_bound(y.begin(),y.end(),yr[i]) - y.begin();
    }

    
    segtree t(y.size() + 1);
    t.upt(0,y.size()-1,n);

    vector<int>xall(n*2);
    for(int i = 0;i < n;i++){
        xall[i] = xl[i];
    }
    for(int i = 0;i < n;i++){
        xall[i + n] = xr[i];
    }
    vector<int>id(n*2);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](int i, int j)->bool
    {
        return xall[i] < xall[j];
    });
    
    vector<int>fa(n + 1, -1);
    for(int i = 0;i < n * 2;i++){
        int p = id[i];
        if(p < n){
            fa[p] = t.qry(yl[p]);
            t.upt(yl[p],yr[p],p);
        }
        else{
            t.upt(yl[p - n],yr[p - n],fa[p - n]);
        }
    }
    
    vector<vector<int>>g(n + 1);
    for(int i = 0;i < n;i++){
        g[fa[i]].push_back(i);
    }

    
    vector<int>dep(n + 1),hson(n + 1, -1),top(n + 1),sz(n + 1,1);
    vector<int>lid(n + 1);
    int tot = 0;
    int root = n;
    lid[root] = tot++;
    top[root] = root;
    auto dfs1 = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            dep[s] = dep[p] + 1;
            self(self, s);
            sz[p] += sz[s];
            if(hson[p] == -1 || sz[hson[p]] < sz[s]){
                hson[p] = s;
            }
        }
    };

    auto dfs2 = [&](auto&&self, int p)->void
    {
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            lid[hson[p]] = lid[p];
            self(self, hson[p]);
        }

        for(auto s : g[p]){
            if(s != hson[p]){
                top[s] = s;
                lid[s] = tot++;
                self(self,s);
            }
        }
    };
    dfs1(dfs1,root);
    dfs2(dfs2,root);

    vector<int>cnt(tot);
    vector<multiset<int>>pq(tot);
    vector<int>tmp(n + 10);
    bit<int>fen(tmp);
    int offset = 3;

    vector<int>open(n,0);
    while(q--){
        char op;
        int p;
        cin>>op>>p;
        p--;
        if(op == '^'){
            open[p]^=1;
            if(open[p] == 1){//open, update cnt, max(pq)
                int r = dep[p], l = dep[p] + 1;
                while(p != -1 && cnt[lid[p]] == 0){
                    l = dep[top[p]];
                    cnt[lid[p]]++;
                    pq[lid[p]].insert(dep[p]);
                    p = fa[top[p]];
                }
                
                if(p != -1){
                    if(dep[p] > *prev(pq[lid[p]].end())){
                        l = *prev(pq[lid[p]].end()) + 1;
                    }
                    cnt[lid[p]]++;
                    pq[lid[p]].insert(dep[p]);
                }
                //cerr<<"add "<<l<<" "<<r<<endl;
                fen.add(r + offset,-1);
                fen.add(l - 1 + offset,1);
            }
            else{
                int r = dep[p], l = dep[p] + 1;
                while(p != -1 && cnt[lid[p]] == 1){
                    l = dep[top[p]];
                    cnt[lid[p]]--;
                    pq[lid[p]].extract(dep[p]);
                    p = fa[top[p]];
                }
                if(p != -1){
                    assert(cnt[lid[p]] >= 2);
                    cnt[lid[p]]--;
                    pq[lid[p]].extract(dep[p]);
                    if(*prev(pq[lid[p]].end()) < dep[p]){
                        l = *prev(pq[lid[p]].end()) + 1;
                    }
                    
                }
                //cerr<<"sub "<<l<<" "<<r<<endl;
                fen.add(r + offset, 1);
                fen.add(l - 1 + offset, -1);
            }
        }
        else{
            p++;
            cout<<fen.qry(p + offset)<<endl;
        }
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