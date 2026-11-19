#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n;
    string s;
    cin >> n >> s;

    constexpr int inf = 1e9;
    vector<array<int,2>>dp(n, {-inf, -inf});

    auto same = [&](int i , int j)->int
    {
        if(i < 0 || j < 0 || i >= n || j >= n)return 0;
        else return (s[i] == s[j]);
    };

    auto d = [&](int i, int j)->int
    {
        if(i < 0)return 0;
        else return dp[i][j];
    };

    
    dp[0][0] = 0;
    for(int i = 1;i < n;i++){
        dp[i][0] = max(dp[i][0], dp[i - 1][0] + same(i, i - 1));
        dp[i][0] = max(dp[i][0], dp[i - 1][1] + same(i, i - 2));
        dp[i][0] = max(dp[i][0], d(i - 2, 1) + same(i, i - 1) + same(i - 3, i - 1));
        

        dp[i][1] = max(dp[i][1], d(i - 2, 0) + same(i, i - 1) + same(i, i - 2));
        dp[i][1] = max(dp[i][1], d(i - 2, 1) + same(i, i - 1) + same(i, i - 3));
    }

    int ans = max(dp[n - 1][0], dp[n - 1][1]);
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}