#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class segtree{
    int n;
    vector<int>tree;
    vector<int>lmax;
    vector<int>rmax;
    vector<int>all;

public:
    segtree(int n_)
    {
        n = n_;
        tree.resize(n*4,-2);
        lmax.resize(n*4,-1);
        rmax.resize(n*4,-1);
        all.resize(n*4,-2);
        build(0,n-1,1);
    }

private:

    void build(int l, int r ,int p)
    {
        if(l != r){
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m+1,r,p*2+1);
            push_up(p);
        }
    } 

    void push_up(int p)
    {
        lmax[p] = max(all[p*2] + lmax[p*2+1] + 1, lmax[p * 2]);
        rmax[p] = max(rmax[p*2] + all[p*2+1] + 1,rmax[p * 2 + 1]);
        tree[p] = max({tree[p*2],tree[p*2+1],rmax[p*2] + lmax[p*2+1] + 1});
        all[p] = all[p*2]+all[p*2+1] + 1;
    }

    void assign(int pos,int val, int l, int r ,int p)
    {
        if(l == r && l == pos){
            if(val == 1){
                lmax[p] = rmax[p] = tree[p] = all[p] = 0;
            }
            if(val == -1){
                lmax[p] = rmax[p] = -1;
                tree[p] = all[p] = -2;
            }
        }else{
            int m = l + r >> 1;
            if(pos <= m)assign(pos,val,l,m,p*2);
            if(pos > m)assign(pos,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

public:
    void assign(int pos ,int val)
    {
        assign(pos,val,0,n-1,1);
    }

    int get_ans()
    {
        return (tree[1] + 1)/2;
    }

};


class segtree_maxmax
{
    int n;
    vector<int>tree;
    vector<int>lazy;
    vector<int>ma;

public:
    segtree_maxmax(int n_)
    {
        n = n_;
        tree.resize(n * 4);
        lazy.resize(n * 4);
        ma.resize(n);
    }

private:

    void push_up(int p)
    {
        tree[p] = max(tree[p * 2],tree[p * 2 + 1]);
    }

    void push_down(int p)
    {
        tree[p * 2] = max(tree[p * 2],lazy[p]);
        tree[p * 2 + 1] = max(tree[p * 2 + 1],lazy[p]);
        lazy[p * 2] = max(lazy[p * 2],lazy[p]);
        lazy[p * 2 + 1] = max(lazy[p * 2 + 1],lazy[p]);
        lazy[p] = 0;
    }

    void range_max(int s, int t ,int val, int l , int r ,int p)
    {
        if(s <= l && r <= t){
            tree[p] = max(tree[p],val);
            lazy[p] = max(lazy[p],val);
            return;
        }else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_max(s,t,val,l,m,p*2);
            if(t > m)range_max(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

    void dfs(int l, int r, int p)
    {
        if(l == r){
            ma[l] = tree[p];
        }else{
            push_down(p);
            int m = l + r >> 1;
            dfs(l,m,p*2);
            dfs(m+1,r,p*2+1);
            push_up(p);
        }
    }

public:
    void range_max(int l, int r ,int val)
    {
        if(l <= r)range_max(l,r,val,0,n-1,1);
    }

    vector<int> query()
    {
        dfs(0,n-1,1);
        return ma;
    }
};

void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        a[i]--;
    }
    vector<vector<array<int,3>>>opt(n);//time pos in/out
    for(int i = 0;i < n;i++){
        opt[a[i]].push_back({0,i,1});
    }
    for(int i = 1;i <= q;i++){
        int p,v;
        cin>>p>>v;
        p--,v--;
        opt[a[p]].push_back({i,p,-1});
        opt[v].push_back({i,p,1});
        a[p] = v;
    }
    segtree t(n);
    segtree_maxmax tmax(q + 1);
    for(int i = 0;i < n;i++){
        opt[i].push_back({q + 1,-1,0});
        for(int j = 0;j < opt[i].size() - 1;j++){
            auto [ti,pos,op] = opt[i][j];
            t.assign(pos,op);
            tmax.range_max(ti,opt[i][j + 1][0]-1,t.get_ans());
           
        }
        for(int j = opt[i].size() - 2;j >= 0;j--){
            auto [ti,pos,op] = opt[i][j];
            t.assign(pos,-op);
        }
    }
    auto ans = tmax.query();
    for(int i = 1;i <= q;i++){
        cout<<ans[i]<<" ";
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