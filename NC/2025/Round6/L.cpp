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
    int n, m;
    cin>>n>>m;
    int cnt = 0;
    string ans(n*2,' ');
    vector<ll>tmp(n * 2 + 5);
    bit<ll>t(tmp);
    int offset = 2;
    for(int i = 0;i < m;i++){
        int l, r;
        cin>>l>>r;
        l--,r--;
        if(t.qry(l + offset, r + offset) == 0){
            ans[l] = '(';
            t.add(l + offset, 1);
            cnt++;
        }
    }
    for(int i = 0;i < n * 2;i++){
        if(ans[i] == ' ' && cnt < n){
            ans[i] = '(';
            cnt++;
        }
        else if(ans[i] == ' '){
            ans[i] = ')';
        }
    }
    cerr<<ans<<endl;

    int sum = 0;
    for(int i = 0;i < n * 2;i++){
        sum += (ans[i] == '(' ? 1 : -1);
        if(sum < 0){
            cout<<-1<<endl;
            return;
        }
    }
    cout<<ans<<endl;
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