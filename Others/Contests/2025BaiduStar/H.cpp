#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int P = 1e9 + 7;

struct segtree{
    int n;
    vector<int>tree;
    vector<int>lazy;
    segtree(int n)
    {
        this->n = n;
        tree.resize(n * 4);
        lazy.resize(n * 4, 1);
        //cerr << tree.size() << endl;
        //build(0, n - 1, 1);
    };

    // void build(int l ,int r, int p)
    // {
        
    // };

    void push_up(int p)
    {
        tree[p] = (tree[p * 2] + tree[p * 2 + 1]) % P;
        return;
    }

    void push_down(int p)
    {
        if(lazy[p] == 1)return;
        tree[p * 2] = 1ll * tree[p * 2] * lazy[p] % P;
        tree[p * 2 + 1] = 1ll * tree[p * 2 + 1] * lazy[p] % P;
        lazy[p * 2] = 1ll * lazy[p * 2] * lazy[p] % P;
        lazy[p * 2 + 1] = 1ll * lazy[p * 2 + 1] * lazy[p] % P;
        lazy[p] = 1;
        return;
    }

    int sum(int s, int t, int l, int r, int p)
    {
        if(s <= l && t >= r){
            return tree[p];
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            int res = 0;
            if(m >= s)res = sum(s,t,l,m,p*2);
            if(m + 1 <= t)res = (res + sum(s,t,m+1,r,p*2+1)) % P;
            push_up(p);
            return res;
        }
    }

    void add(int x, int val, int l, int r, int p)
    {
        if(x == l && x == r){
            tree[p] = (tree[p] + val) % P;
            return;
        }
        int m = l + r >> 1;
        push_down(p);
        if(x <= m)add(x, val, l, m, p * 2);
        else add(x, val, m + 1, r, p * 2 + 1);
        push_up(p);
        return;
    }

    void mul(int s, int t,int val, int l, int r, int p)
    {
        if(s <= l && t >= r){
            tree[p] = 1ll * tree[p] * val % P;
            lazy[p] = 1ll * lazy[p] * val % P;
            return;
        }
        else{
            int m = l + r >> 1;
            push_down(p);
            int res = 0;
            if(m >= s)mul(s,t,val,l,m,p*2);
            if(m + 1 <= t)mul(s,t,val,m+1,r,p*2+1);
            push_up(p);
            return;
        }
    }

    int get(int x, int l, int r, int p)
    {
        if(x == l && x == r){
            return tree[p];
        }
        int m = l + r >> 1;
        push_down(p);
        int res = 0;
        if(x <= m)res = get(x, l, m, p * 2);
        else res = get(x, m + 1, r, p * 2 + 1);
        push_up(p);
        return res;
    }

    int sum(int l, int r)
    {
        if(l > r)return 0;
        return sum(l, r, 0, n - 1,1);
    }

    void add(int x, int val)
    {
        add(x, val, 0, n - 1, 1);
        return;
    }

    void mul(int l, int r, int val)
    {
        if(l > r)return;
        mul(l,r, val, 0, n- 1, 1);
    }

    int get(int x)
    {
        return get(x, 0, n-1,1);
    }
};

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    auto b = a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()), b.end());
    for(int i = 0;i < n;i++){
        a[i] = lower_bound(b.begin(),b.end(), a[i]) - b.begin();
    }

    

    int inv100 = power(100, P - 2);
    int lp = 1ll * x * inv100 % P, rp = 1ll * (100 - x) * inv100 % P;
    segtree t(n);
    t.add(a[0], 1);
    for(int i = 0;i < n;i++){
        //cerr << t.get(i) << endl;
    }
    for(int i = 1;i < n;i++){
        int l = t.sum(0, a[i] - 1), r = t.sum(a[i] + 1, n - 1);
        t.add(a[i], (1ll * l * rp + 1ll * r * lp) % P);
        t.mul(0, a[i] - 1, lp);
        t.mul(a[i] + 1, n - 1, rp);
    }

    ll ans = 0;
    for(int i = 0;i < n;i++){
        //cerr << t.get(i) << endl;
        ans = (ans + 1ll * b[i] * t.get(i)) % P;
    }
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt ;
    while(tt--){
        solve();
    }
    return 0;
}