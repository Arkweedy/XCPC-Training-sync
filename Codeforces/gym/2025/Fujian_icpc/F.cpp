#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<bool isMin>//isMin : find less max
class segtree
{
    int n;  
    vector<int>tree;
    
public:
    segtree(int _n)
    {
        n = _n;
        tree.resize(n * 4);
        build(0,n-1,1);
    }

private:
    void build(int l, int r, int p)
    {
        if(l == r){
            if constexpr(isMin){
                tree[p] = INT_MAX;
            }
            else{
                tree[p] = -1;
            }
        }
        else{
            int m = l + r >> 1;
            build(l, m,p * 2);
            build(m + 1, r,p * 2 + 1);
            push_up(p);
        }
    }

    void push_up(int p)
    {
        if constexpr(isMin){
            tree[p] = min(tree[p * 2], tree[p * 2 + 1]);
        }
        else{
            tree[p] = max(tree[p * 2], tree[p * 2 + 1]);
        }
    }

    void upt(int pos,int val, int l, int r, int p)
    {
        if(l == pos && r == pos){
            tree[p] = val;
        }
        else{
            int m = l + r >> 1;
            if(pos <= m)upt(pos,val,l,m, p * 2);
            else upt(pos,val,m+1,r,p*2+1);
            push_up(p);
        }
        return;
    }

    bool ok(int val,int p)
    {
        if constexpr(isMin){
            return val > tree[p];
        }
        else{
            return val < tree[p];
        }
    }

    int find(int val,int s, int t, int l, int r, int p)
    {
        if(s <= l && r <= t){//cover
            if(ok(val, p)){
                if(l == r)return l;
                //else continue binary search, not return
            }else{
                return -1;
            }
        }
        
        int m = l + r >> 1;
        if constexpr(isMin){
            if(m < t){
                int res = find(val,s,t,m + 1, r, p * 2 + 1);
                if(res != -1)return res;
            }
            if(s <= m){
                return find(val,s,t,l, m,p * 2);
            }
            return -1;
        }
        else{
            if(s <= m){
                int res = find(val,s,t,l, m,p * 2);
                if(res != -1)return res;
            }
            if(m < t){
                return find(val,s,t,m + 1, r, p * 2 + 1);
            }
            return -1;
        }
    }

public:
    int find(int val, int s, int t)
    {
        return find(val,s,t,0,n-1,1);
    }

    void upt(int pos, int val)
    {
        upt(pos,val,0,n-1,1);
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
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin>>x[i];
    }
    for(int i = 0;i < n;i++){
        cin>>y[i];
    }

    segtree<1>lmax(n);
    segtree<0>rmin(n);
    
    vector<int>id(n);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](int i, int j)->bool
    {
        return x[i] == x[j] ? y[i] < y[j] : x[i] < x[j];
    });

    vector<int>l(n),r(n);

    
    for(int i = 0;i < n;i++){
        l[id[i]] = lmax.find(y[id[i]],0,id[i]);
        lmax.upt(id[i],y[id[i]]);
    }
    for(int i = n - 1;i >= 0;i--){
        r[id[i]] = rmin.find(y[id[i]],id[i],n-1);
        rmin.upt(id[i],y[id[i]]);
    }
    
    vector<int>tmp(n + 1);
    bit<int>t(tmp);
    
    vector<int>ql(q),qr(q);
    for(int i = 0;i < q;i++){
        cin>>ql[i]>>qr[i];
        ql[i]--,qr[i]--;
    }
    vector<int>idl(n),idr(n);
    iota(idl.begin(),idl.end(),0);
    iota(idr.begin(),idr.end(),0);
    sort(idl.begin(),idl.end(),[&](int i, int j)->bool
    {
        return ql[i] < ql[j];
    });
    sort(idr.begin(),idr.end(),[&](int i, int j)->bool
    {
        return qr[i] < qr[j];
    });

    for(int i = 0;i < q;i++){
        cerr<<l[i]<<" ";
    }
    cerr<<endl;
    for(int i = 0;i < q;i++){
        cerr<<r[i]<<" ";
    }
    cerr<<endl;

    //i is ok when in (l_i, r_i)
    

    vector<int>ans(q);
    int pl = 0, pr = 0;
    int offset = 2;
    while(pl < q && ql[idl[pl]] == 0)pl++;
    for(int i = 0;i < n;i++){
        t.add(l[i] + offset, 1);//offset = 2
        while(pl < q && ql[idl[pl]] - 1 == i){
            ans[idl[pl]] -= t.qry(ql[idl[pl]] + offset);
            pl++;
        }
        while(pr < q && qr[idr[pr]] == i){
            ans[idr[pr]] += t.qry(ql[idr[pr]] + offset);//query is l !!! 
            pr++;
        }
    }
    for(int i = 0;i < q;i++){
        cout<<ans[i]<<endl;
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