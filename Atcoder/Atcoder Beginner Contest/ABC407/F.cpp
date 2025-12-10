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
    vector<T>lazy;
    vector<int>len;

public:
    vector<T>a;

    segtree(int _n)
    {
        n = _n;
        a.resize(n);
        len.resize(n * 4);
        tree.resize(n * 4);
        lazy.resize(n * 4);
        build(0,n-1,1);
    }

private:

    void build(int l, int r, int p)
    {
        if(l == r){
            len[p] = 1;
        }else{
            int m = l + r >> 1;
            build(l, m, p*2);
            build(m + 1,r,p * 2 + 1);
            len[p] = len[p * 2] + len[p * 2 + 1];
        }
    }

    void push_up(int p)
    {
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }

    void push_down(int p)
    {
        tree[p * 2] += lazy[p] * len[p * 2];
        tree[p * 2 + 1] += lazy[p] * len[p * 2 + 1];
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        lazy[p] = 0; 
    }

    void range_add(int s, int t, T val, int l, int r, int p)
    {
        if(s <= l && r <= t){
            tree[p] += val;
            lazy[p] += val;
        }else{
            int m = l + r >> 1;
            push_down(p);
            if(s <= m)range_add(s,t,val,l,m,p*2);
            if(t > m)range_add(s,t,val,m+1,r,p*2+1);
            push_up(p);
        }
        return;
    }

    void get(int l, int r, int p)
    {
        if(l == r){
            a[l] = tree[p];
        }else{
            push_down(p);
            int m = l + r >> 1;
            get(l,m,p*2);
            get(m+1,r,p*2+1);
        }
    }

public:
    void get()
    {
        get(0,n-1,1);
    }

    void range_add(int l, int r, T val)
    {
        range_add(l,r,val,0,n-1,1);
    }

};


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    vector<int>l(n + 1, 1),r(n + 1, n);
    stack<int>st;
    for(int i = 1;i <= n;i++){
        while(!st.empty() && a[i] >= a[st.top()]){
            r[st.top()] = i - 1;
            st.pop();
        }
        st.push(i);
    }
    while(!st.empty())st.pop();
    for(int i = n;i >= 1;i--){
        while(!st.empty() && a[i] > a[st.top()]){
            l[st.top()] = i + 1;
            st.pop();
        }
        st.push(i);
    }
    
    segtree<ll>t(n + 2);
    for(int i = 1;i <= n;i++){
        int len = r[i] - l[i] + 1;
        int ma = min(i - l[i] + 1, r[i] - i + 1);
        if(len % 2 == 0){
            t.range_add(1,ma,a[i]);
            t.range_add(len+1-ma+1,len+1,-a[i]);
        }else{
            t.range_add(1,ma,a[i]);
            t.range_add(len+1-ma+1,len+1,-a[i]);
        }
    }
    t.get();
    auto sum = t.a;
    for(int i = 1;i <= n;i++){
        sum[i] += sum[i - 1];
    }
    for(int i = 1;i <= n;i++){
        cout<<sum[i]<<"\n";
    }
    cout<<endl;
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