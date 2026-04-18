#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

#define f(i, l, r) for (int i = (l), _end = (r); i <= _end; ++i)
#define fx(i, l, r) for (int i = (l), _end = (r); i < _end; ++i)


//Create time: 2026.04.10 09:16:24

void solve()
{
    int n;
    cin >> n;
    static ll a[500001];
    f(i, 1, n) cin >> a[i];
    static pair<int, int> lr[500001];
    int m;
    cin >> m;
    fx(i, 0, m) cin >> lr[i].first >> lr[i].second;
    sort(lr, lr + m, [](auto x, auto y){ return x.second < y.second; });
    static int lpre[500001], r[500001];
    lpre[0] = lr[0].first;
    fx(i, 1, m) lpre[i] = max(lr[i].first, lpre[i-1]);
    fx(i, 0, m) r[i] = lr[i].second;
    static ll dp[500001];
    deque<pair<int, ll>> q;
    dp[0] = 0;
    q.push_back({0, 0});
    f(i, 1, n) {
        int j = lower_bound(r, r + m, i) - r;
        int l = 0;
        if (j != 0) l = lpre[j - 1];
        while (!q.empty() && q.front().first < l)
            q.pop_front();
        ll mx = q.front().second;
        dp[i] = mx + a[i];
        while (!q.empty() && q.back().second > dp[i])
            q.pop_back();
        q.push_back({i, dp[i]});
        //printf("dp[%d]=%d\n", i, dp[i]);
    }
    ll ans = 1e18;
    f(i, lpre[m-1], n)
        ans = min(ans, dp[i]);
    printf("%lld\n", ans);
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