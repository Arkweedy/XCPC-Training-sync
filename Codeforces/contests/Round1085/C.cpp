#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.08 23:33:21

void solve()
{
    int n, h;
    cin >> n >> h;
    vector<int>a(n + 2);
    i64 sum = 1ll * n * h;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        sum -= a[i];
    }
    vector<i64>pa(n + 2);
    for(int i = 1;i <= n + 1;i++){
        pa[i] = pa[i - 1] + a[i];
    }

    vector<int>pre(n + 2), suf(n + 2);
    vector<int>stk;
    for(int i = 1;i <= n;i++){
        while(!stk.empty() && a[i] > a[stk.back()]){
            suf[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }
    while(!stk.empty()){
        suf[stk.back()] = n + 1;
        stk.pop_back();
    }

    for(int i = n;i >= 1;i--){
        while(!stk.empty() && a[i] >= a[stk.back()]){
            pre[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }
    while(!stk.empty()){
        pre[stk.back()] = 0;
        stk.pop_back();
    }

    vector<i64>sx(n + 2),px(n + 2);
    for(int i = n;i >= 1;i--){
        sx[i] = sx[suf[i]] + 1ll * (suf[i] - i) * a[i] - (pa[suf[i] - 1] - pa[i - 1]);
    }
    for(int i = 1;i <= n;i++){
        px[i] = px[pre[i]] + 1ll * (i - pre[i]) * a[i] - (pa[i] - pa[pre[i]]);
    }
    
    int len = __lg(n) + 1;
    vector<vector<int>>p(len, vector<int>(n + 1));
    for(int i = 1;i <= n;i++){
        p[0][i] = i; 
    }

    auto maxp = [&](int x, int y)->int
    {
        return a[x] > a[y] ? x : y;
    };

    for(int i = 1;i < len;i++){
        for(int j = 1;(j + (1 << i) - 1) <= n;j++){
            p[i][j] = maxp(p[i - 1][j], p[i - 1][j + (1 << i - 1)]);
        }
    }

    auto rmq = [&](int l, int r)->int
    {
        int len = r - l + 1;
        int k = __lg(len);
        return maxp(p[k][l], p[k][r - (1 << k) + 1]);
    };

    i64 ans = LLONG_MAX / 2;
    for(int i = 1;i <= n;i++){
        ans = min(ans, px[i] + sx[i]);
    }
    for(int i = 1;i + 1 <= n;i++){
        for(int j = i + 1;j <= n;j++){
            int p = rmq(i, j);
            i64 res = px[i] + sx[j] + (sx[i] - sx[p]) + (px[j] - px[p]);
            ans = min(ans, res);
        }
    }
    cout << sum - ans << endl;
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