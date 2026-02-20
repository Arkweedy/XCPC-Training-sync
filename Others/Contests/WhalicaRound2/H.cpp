#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//H.cpp Create time : 2026.02.15 15:29

constexpr int P = 998244353;

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

constexpr int inf = 1e9;

struct segtree
{
    int n;
    vector<int>sum, emp, mex;

    segtree(int m) : n(m), sum(m * 4), emp(m * 4), mex(m * 4)
    {
        build(1, n, 1);
    }

    void build(int l, int r, int p)
    {
        if(l == r){
            mex[p] = l;
            sum[p] = l;
            emp[p] = 1;
            return;
        }
        int m = l + r >> 1;
        build(l, m, p * 2);
        build(m + 1, r, p * 2 + 1);
        pull(p);
        return;
    }

    void pull(int p)
    {
        mex[p] = min(mex[p * 2], mex[p * 2 + 1]);
        emp[p] = emp[p * 2] + emp[p * 2 + 1];
        sum[p] = (sum[p * 2] + 1ll * sum[p * 2 + 1] * power(2, emp[p * 2])) % P;
        return;
    }

    void apply(int x, int val, int l, int r, int p)
    {
        if(l == r){
            if(val == 0){
                emp[p] = 1;
                mex[p] = x;
                sum[p] = x;
            }
            else{
                emp[p] = 0;
                mex[p] = inf;
                sum[p] = 0;
            }
            return;
        }
        int m = l + r >> 1;
        if(x <= m)apply(x, val, l, m, p * 2);
        else apply(x, val, m + 1, r, p * 2 + 1);
        pull(p);
        return;
    }

    void apply(int x, int val)
    {
        apply(x, val, 1, n, 1);
    }

    int get3()
    {
        return mex[1];
    }

    int get4()
    {
        return sum[1] * 2 % P;
    }
};

void solve()
{
    int n;
    cin >> n;
    segtree t(n);
    int q;
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            int x;
            cin >> x;
            t.apply(x, 1);
        }
        else if(op == 2){
            int x;
            cin >> x;
            t.apply(x, 0);
        }
        else if(op == 3){
            cout << t.get3() << "\n";
        }
        else if(op == 4){
            cout << t.get4() << "\n";
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