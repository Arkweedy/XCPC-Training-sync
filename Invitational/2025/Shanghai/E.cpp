#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


constexpr int inf = (1<<30) + 1;

class segtree{
    int n;
    vector<ll>a;
    vector<ll>tree;
    vector<ll>lcms;
    vector<ll>gcds;
    vector<ll>lazy;
    vector<ll>len;

public:
    segtree(vector<ll>arr)
    {
        n = arr.size();
        a = arr;
        tree.resize(n * 4);
        lcms.resize(n * 4);
        gcds.resize(n * 4);
        lazy.resize(n * 4,-1);
        len.resize(n * 4);
        build(0,n-1,1);
    }

private:

    void build(int l, int r, int p)
    {
        if(l == r){
            tree[p] = a[l];
            lcms[p] = a[l];
            gcds[p] = a[l];
            len[p] = 1;
        }
        else{
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m+1,r,p*2+1);
            len[p] = len[p * 2] + len[p * 2 + 1];//only update once
            push_up(p);
        }
    }

    void push_up(int p)
    {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
        gcds[p] = gcd(gcds[p * 2], gcds[p * 2 + 1]);
        if(lcms[p * 2] >= inf || lcms[p * 2 + 1] >= inf){
            lcms[p] = max(lcms[p * 2],lcms[p * 2 + 1]);
        }else{
            lcms[p] = lcm(lcms[p * 2], lcms[p * 2 + 1]);
        }
    }

    void push_down(int p)
    {
        if(lazy[p] != -1){
            tree[p * 2] = lazy[p] * len[p * 2];
            tree[p * 2 + 1] = lazy[p] * len[p * 2 + 1];
            lcms[p * 2] = lcms[p * 2 + 1] = lazy[p];
            gcds[p * 2] = gcds[p * 2 + 1] = lazy[p];
            lazy[p * 2] = lazy[p * 2 + 1] = lazy[p];
            lazy[p] = -1;
        }
    }

    void range_assign(int s, int t, int val, int l, int r, int p)
    {
        if(s <= l && r <= t){
            tree[p] = val * len[p];
            lcms[p] = val;
            gcds[p] = val;
            lazy[p] = val;
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_assign(s,t,val,l,m,p*2);
            if(t > m)range_assign(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
        return;
    }

    ll range_gcd(int s, int t,int val, int l, int r, int p)
    {
        if(s <= l && r <= t){
            if(val % lcms[p] == 0){
                return tree[p];
            }
            else if(gcds[p] == lcms[p]){//same
                lcms[p] = gcds[p] = gcd(gcds[p],val);
                tree[p] = gcds[p] * len[p];
                lazy[p] = gcds[p];
                return tree[p];
            }else{
                int m = l + r >> 1;
                push_down(p);
                ll res = range_gcd(s,t,val,l,m,p*2) + range_gcd(s,t,val,m+1,r,p*2+1);
                push_up(p);
                return res;
            }
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            ll res = 0;
            if(s <= m)res += range_gcd(s,t,val,l,m,p*2);
            if(t > m)res += range_gcd(s,t,val,m+1,r,p*2+1);
            push_up(p);
            return res;
        }
    }


public:
    void range_assign(int l, int r, int val)
    {
        range_assign(l,r,val,0,n-1,1);
    }

    ll range_gcd(int l,int r, int val)
    {
        return range_gcd(l,r,val,0,n-1,1);
    }
};


void solve()
{
    int n,q;
    cin>>n>>q;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    segtree t(a);
    
    while(q--){
        int op,l,r,x;
        cin>>op>>l>>r>>x;
        l--,r--;
        if(op == 0){
            t.range_assign(l,r,x);
        }
        else{
            cout<<t.range_gcd(l,r,x)<<endl;
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