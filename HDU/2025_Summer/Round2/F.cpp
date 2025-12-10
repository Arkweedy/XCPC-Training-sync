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
    vector<int>a(n + 1),b(n + 1);
    vector<int>rkb(n + 1);
    vector<int>ans(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
        ans[a[i]] += i - 1;
    }
    for(int i = 1;i <= n;i++){
        cin>>b[i];
        rkb[b[i]] = i;
        ans[b[i]] += i - 1;
    }
    vector<int>tmp(n + 5);
    bit<int>t(tmp);

    for(int i = 1;i <= n;i++){
        int p = a[i];
        ans[p] -= t.qry(rkb[p]);
        t.add(rkb[p], 1);
    }

    for(int i = 1;i <= n;i++){
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