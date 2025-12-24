#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//H.cpp Create time : 2025.12.23 23:56

void solve()
{
    int n, q;
    cin >> n >> q;
    int k = __lg(n) + 1;
    vector<vector<i64>>d1(k, vector<i64>(n + 1)), d2(k, vector<i64>(n + 1));

    auto add_s = [&](int l, int r, int k)->void
    {
        
        int len = 1 << k;
        i64 v = 1ll * max(1, len / 2) * len;
        int L = l + (1 << k) - 1;
        int R = l + ((r - l + 1) / len + 1) * len - 1;
        int x = (R - l) / len;
        if(L <= n)d2[k][L] += v;
        if(R <= n)d2[k][R] -= v;
        if(R <= n)d1[k][R] -= v * x;
        return;
    };

    auto add = [&](int l, int r)->void
    {
        int len = r - l + 1;
        for(int i = 0; (1 << i) <= len;i++){
            add_s(l, r, i);
        }
        return;
    };

    vector<i64>a(n + 1);
    auto calc = [&]()->void
    {
        for(int i = 0;i < k;i++){
            vector<i64>b(n + 1),c(n + 1);
            int d = 1 << i;
            for(int j = 1;j <= n;j++){
                b[j] = d2[i][j];
                if(j >= d)b[j] += b[j - d];
            }
            for(int j = 1;j <= n;j++){
                c[j] = b[j] + d1[i][j];
                if(j >= d)c[j] += c[j - d];
                a[j] += c[j];
            }
        }
    };

    while(q--){
        int l, r;
        cin >> l >> r;
        add(l, r);
    }

    calc();
    for(int i = 1;i <= n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
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