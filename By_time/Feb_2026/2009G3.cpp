#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//2009G3.cpp Create time : 2026.02.21 01:41

//离线下来写？

void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i] -= i;
        a[i] += n - 1;
    }
    //0, n - 2
    vector<int>c(n * 2 + 10), cc(n * 2 + 10);
    int ma = 0;
    cc[0] = n * 2;
    auto add = [&](int x, int cnt)->void
    {
        if(cnt == -1){
            cc[c[x]]--;
            c[x]--;
            cc[c[x]]++;
            while(cc[ma] == 0)ma--;
        }
        else{
            cc[c[x]]--;
            c[x]++;
            cc[c[x]]++;
            while(cc[ma + 1] != 0)ma++;
        }
        return;
    };

    vector<int>b(n - k + 1);

    for(int i = 0;i < k - 1;i++){
        add(a[i], 1);
    }

    for(int i = 0;i < n - k + 1;i++){
        add(a[i + k - 1], 1);
        b[i] = k - ma;
        add(a[i], -1);
    }

    vector<pair<int,int>>qry(q);
    for(int i = 0;i < q;i++){
        int l, r;
        cin >> l >> r;
        l--,r--;
        r -= k - 1;
        qry[i] = {l, r};
    }

    int m = n - k + 1;
    vector<int>pre(m), suf(m);
    vector<int>stk;
    for(int i = 0;i < m;i++){
        while(!stk.empty()){
            if(b[stk.back()] > b[i]){
                suf[stk.back()] = i;
                stk.pop_back();
            }
            else{
                break;
            }
        }
        stk.push_back(i);
    }
    while(!stk.empty()){
        suf[stk.back()] = m;
        stk.pop_back();
    }

    for(int i = m - 1;i >= 0;i--){
        while(!stk.empty()){
            if(b[stk.back()] >= b[i]){
                pre[stk.back()] = i;
                stk.pop_back();
            }
            else{
                break;
            }
        }
        stk.push_back(i);
    }
    while(!stk.empty()){
        pre[stk.back()] = -1;
        stk.pop_back();
    }

    vector<i64>f(m),g(m);
    for(int i = m - 1;i >= 0;i--){
        f[i] = 1ll * b[i] * (suf[i] - i);
        if(suf[i] < m)f[i] += f[suf[i]];
    }
    for(int i = 0;i < m;i++){
        g[i] = 1ll * b[i] * (i - pre[i]);
        if(pre[i] >= 0)g[i] += g[pre[i]];
    }
    vector<i64>pf(m),pg(m);
    for(int i = 0;i < m;i++){
        pf[i] = f[i];
        pg[i] = g[i];
        if(i > 0){
            pf[i] += pf[i - 1];
            pg[i] += pg[i - 1];
        }
    }

    auto F = [&](int l, int r)->i64
    {
        if(r < l)return 0;
        i64 res = pf[r];
        if(l > 0)res -= pf[l - 1];
        return res;
    };

    auto G = [&](int l, int r)->i64
    {
        if(r < l)return 0;
        i64 res = pg[r];
        if(l > 0)res -= pg[l - 1];
        return res;
    };

    //rmq
    int len = __lg(m) + 1;
    vector<vector<int>>p(len, vector<int>(m));
    for(int i = 0;i < m;i++){
        p[0][i] = i;
    }

    auto minp = [&](int x, int y)->int
    {
        // assert(x >= 0 && x < m);
        // assert(y >= 0 && y < m);
        if(b[x] == b[y])return x < y ? x : y;
        return b[x] < b[y] ? x : y;
    };

    for(int i = 1;i < len;i++){
        for(int j = 0;(j + (1 << i) - 1) < m;j++){
            p[i][j] = minp(p[i - 1][j], p[i - 1][j + (1 << i - 1)]);
        }
    }

    auto rmq = [&](int l, int r)->int
    {
        int len = r - l + 1;
        int k = __lg(len);
        return minp(p[k][l], p[k][r - (1 << k) + 1]);
    };

    vector<i64>ans(q);
    for(int i = 0;i < q;i++){
        auto [l, r] = qry[i];
        int x = rmq(l, r);
        ans[i] = 1ll * b[x] * (x - l + 1) * (r - x + 1) + F(l, x - 1) - (x - l) * f[x] + G(x + 1, r) - (r - x) * g[x];
    }
    for(int i = 0;i < q;i++){
        cout << ans[i] << "\n";
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