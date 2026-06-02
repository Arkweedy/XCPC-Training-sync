#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.05.31 16:24:46

void solve()
{
    int n;
    cin >> n;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
    }

    auto s = [&](int i, int j, int k)->i64
    {
        return abs(1ll * (x[i] - x[j]) * (y[k] - y[j]) - 1ll * (x[k] - x[j]) * (y[i] - y[j]));
    };
    constexpr i64 inf = 1e18;
    vector<vector<i64>>dp(n, vector<i64>(n, -inf));
    for(int i = 0;i < n;i++){
        int k = (i + 1) % n;
        for(int j = (i + 2) % n;j % n != (i - 3 + n) % n;j++){
            while(s(i, j % n, k) < s(i, j % n, (k + 1) % n)){
                k++;
                k %= n;
            }
            dp[i][j % n] = s(i, j % n, k);
        }
    }

    for(int d = 2;d <= n - 3;d++){
        for(int i = 0;i < n;i++){
            dp[i][(i + d) % n] = max(dp[i][(i + d) % n], dp[(i + 1) % n][(i + d) % n]);
            dp[i][(i + d) % n] = max(dp[i][(i + d) % n], dp[i][(i + d - 1) % n]);
        }
    }
    
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        for(int j = (i + 2) % n;j % n != (i - 3 + n) % n;j++){
            ans = max(ans, dp[i][j % n] + dp[(j + 1) % n][(i - 1 + n) % n]);
        }
    }

    cout << ans << endl;
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