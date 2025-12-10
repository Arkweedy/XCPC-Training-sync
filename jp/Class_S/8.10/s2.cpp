#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<typename T>
class segtree // 单点加， 区间求和
{
private:
    int n;
    vector<T>arr;
    vector<T>tree;
    vector<T>lazy;
    vector<int>len;

public:
    segtree(vector<T>a)
    {
        n = a.size();
        arr = a;
        tree.resize(n * 4);
        lazy.resize(n * 4);
        len.resize(n * 4);
        build(0,n - 1,1);
    }

    segtree(int _n)
    {
        n = _n;
        arr = vector<T>(n);
        tree.resize(n * 4);
        lazy.resize(n * 4);
        len.resize(n * 4);
        build(0,n - 1,1);
    }

private:
    void build(int l, int r, int p)
    {
        if(l == r){
            tree[p] = arr[l];
            len[p] = 1;
        }
        else{
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m + 1,r,p*2+1);
            len[p] = len[p * 2] + len[p * 2 + 1];
            push_up(p);
        }
    }

    void push_up(int p)
    {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void push_down(int p)
    {
        //lazy[p] -> lson ,rson 
        if(lazy[p] == 0){
            tree[p * 2] += lazy[p * 2] * len[p * 2];
            tree[p * 2 + 1] += lazy[p * 2 + 1] * len[p * 2 + 1];
            lazy[p * 2] += lazy[p * 2];
            lazy[p * 2 + 1] += lazy[p * 2 + 1];
            lazy[p] = 0;
        }
    }

    void add(int pos, T val, int l, int r,int p)
    {
        if(l == r){
            assert(l == pos);
            tree[p] += val;
        }
        else{
            int m = l + r >> 1;
            if(pos <= m)add(pos,val,l,m,p*2);
            else add(pos,val,m + 1,r,p*2+1);
            push_up(p);
        }
    }

    void range_add(int s,int t,T val,int l,int r,int p)
    {
        if(s <= l && r <= t){
            tree[p] += val * len[p];
            lazy[p] += val;
        }
        else{
            int m = l + r >> 1;
            int res = 0;
            push_down(p);
            if(s <= m)res += range_add(s,t, val,l,m,p*2);
            if(t > m)res += range_add(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
    }

    T range_sum(int s,int t,int l,int r,int p)
    {
        if(s <= l && r <= t){
            return tree[p];
        }
        else{
            int m = l + r >> 1;
            T res = 0;
            push_up(p);
            if(s <= m)res += range_sum(s,t,l,m,p*2);
            if(t > m)res += range_sum(s,t,m+1,r,p*2+1);
            //push_up(p);
            return res;
        }
    }

    //build
    //push_up
    //push_down
public:
    void add(int pos,int val)
    {
        add(pos,val,0,n-1,1);
    }

    int range_sum(int l, int r)
    {
        return range_sum(l,r,0,n-1,1);
    }

    void range_sum(int l, int r, T val)
    {
        range_sum(l,r,0,n-1,1);
    }

};

void solve()
{
    int n ,m;
    cin>>n>>m;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    segtree t(a);
    while(m--){
        int op, x, y;
        cin>>op>>x>>y;
        if(op == 1){
            x--;
            t.add(x,y);
        }
        else{
            x--,y--;
            cout<<t.range_sum(x,y)<<"\n";
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