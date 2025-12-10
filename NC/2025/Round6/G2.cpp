#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class segtree
{
    int n;
    vector<int>tree;//0 cnt
    vector<int>res;//l 1 cnt
    vector<int>a;

public:
    segtree(vector<int>arr)
    {
        a = arr;
        n = arr.size();
        tree.resize(n * 4);
        res.resize(n * 4);
        build(0,n-1,1);
    }

private:
    void build(int l ,int r ,int p)
    {
        if(l == r){
            if(a[l] == 0)tree[p] = 1;
            else res[p] = 1;
        }
        else{
            int m = l + r >> 1;
            build(l,m,p*2);
            build(m+1,r,p*2+1);
            push_up(p);
        }
    }

    void push_up(int p)
    {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
        res[p] = res[p * 2];
        if(tree[p * 2] == 0)res[p] += res[p * 2 + 1];
    }

    void flip(int pos, int l, int r, int p)
    {
        if(l == r){
            swap(res[p],tree[p]);
        }
        else{
            int m = l + r >> 1;
            if(pos <= m)flip(pos,l,m,p*2);
            else flip(pos,m+1,r,p*2+1);
            push_up(p);
        }
        return;
    }

public:
    void flip(int p)
    {
        flip(p,0,n-1,1);
    }

    int get()
    {
        return res[1];
    }
};


void solve()
{
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        a[i] = (s[i] == 'L' ? '0' : '1');
    }
    segtree t(a);
    while(q--){
        int x;
        cin>>x;
        x--;
        t.flip(x);
        cout<<t.get()<<endl;
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