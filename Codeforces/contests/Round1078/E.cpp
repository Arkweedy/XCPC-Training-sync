#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.08 18:03

//dp

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>a(n, vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j];
        }
    }

    constexpr i64 inf = 1e17;
    
    auto chs = [&](vector<i64>&a, vector<i64>&b)->i64
    {
        int n = a.size();
        //n - 1 a, 1 b
        // a >= b
        //min the max
        i64 ma = -inf;
        int p = -1;
        for(int i = 0;i < n;i++){
            if(a[i] > ma){
                ma = a[i];
                p = i;
            }
        }
        i64 res = -inf;
        for(int i = 0;i < n;i++){
            if(i == p)res = max(res, b[i]);
            else res = max(res, a[i]);
        }
        return res;
    };
   
    i64 ans = 0;
    
    vector<vector<i64>>dp(n, vector<i64>(m, -inf));
    dp[0][0] = a[0][0];
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(i + 1 < n){
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + a[i + 1][j]);
            }
            if(j + 1 < m){
                dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + a[i][j + 1]);
            }
        }
    }
    vector<vector<i64>>rdp(n, vector<i64>(m, -inf));
    rdp[n - 1][m - 1] = a[n - 1][m - 1];
    for(int i = n - 1;i >= 0;i--){
        for(int j = m - 1;j >= 0;j--){
            if(i - 1 >= 0){
                rdp[i - 1][j] = max(rdp[i - 1][j], rdp[i][j] + a[i - 1][j]);
            }
            if(j - 1 >= 0){
                rdp[i][j - 1] = max(rdp[i][j - 1], rdp[i][j] + a[i][j - 1]);
            }
        }
    }
    assert(dp[n - 1][m - 1] == rdp[0][0]);
    ans = dp[n - 1][m - 1];

    for(int i = 0;i < n + m - 1;i++){//x + y // choose which i + j
        vector<i64>r1, r2;
        for(int x = max(0, i - m + 1);x <= min(n - 1, i);x++){
            int y = i - x;
            if(y < 0 || y >= m)continue;
            i64 val1 = dp[x][y] + rdp[x][y] - a[x][y];
            i64 val2 = min(val1, dp[x][y] + rdp[x][y] - 3ll * a[x][y]);
            r1.push_back(val1);
            r2.push_back(val2);
        }
        ans = min(ans, chs(r1, r2));
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