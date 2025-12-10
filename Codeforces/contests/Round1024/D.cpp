#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

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
    int n;
    cin>>n;
    int m = n / 2;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>b(n - m),c(m);
    for(int i = 0;i < n;i++){
        if(i % 2 == 0){
            b[i / 2] = a[i]; 
        }else{
            c[i / 2] = a[i];
        }
    }
    vector<int>e(n + 1);
    bit<int>tb(e), tc(e);
    ll invb = 0, invc = 0;
    for(int i = 0;i < b.size();i++){
        invb += tb.qry(b[i] + 1, n);
        tb.add(b[i], 1);
    }
    for(int i = 0;i < c.size();i++){
        invc += tc.qry(c[i] + 1, n);
        tc.add(c[i],1);
    }
    //cerr<<invb<<" "<<invc<<endl;
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    if((invb%2)^(invc%2) == 1){
        if(n % 2 == 0){
            int x = c.size() - 1;
            swap(c[x],c[x-1]);
        }else{
            int x = b.size() - 1;
            swap(b[x],b[x-1]);
        }
    }
    for(int i = 0;i < n;i++){
        if(i % 2 == 0){
            cout<<b[i/2]<<" ";
        }else{
            cout<<c[i/2]<<" ";
        }
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