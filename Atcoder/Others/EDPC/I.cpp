#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.15 14:55:15

void solve()
{
    int n;
    cin >> n;
    vector<double>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<double>dp(n + 1);
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        vector<double>ndp(n + 1);
        for(int j = 0;j < n;j++){
            ndp[j] += dp[j] * (1 - a[i]);
            ndp[j + 1] += dp[j] * a[i];
        }
        dp = move(ndp);
    }
    double ans = 0;
    for(int i = n / 2 + 1;i <= n;i++){
        ans += dp[i];
    }
    cout << fixed << setprecision(10) << ans << endl;
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