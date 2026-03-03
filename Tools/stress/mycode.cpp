#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1736E.cpp Create time : 2026.02.28 15:01

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    vector<vector<int>>dp(n + 1, vector<int>(n + 1));
    for(int i = 0;i < n;i++){
        for(int j = 0;j <= i;j++){// dp[i][j]
            for(int k = i + 1;k <= n;k++){
                int x = k - i - 1;//move to a[i + 1] steps
                if(x <= i + 1 - j){
                    for(int p = i + 1;p <= n;p++){// a line 
                        dp[p][j + x + p - i - 1] = max(dp[p][j + x + p - i - 1], dp[i][j] + a[k] * (p - i));
                    }
                }
                else break;
            }
        }
    }
    int ans = 0;
    for(int i = 0;i <= n;i++){
        ans = max(ans, dp[n][i]);
    }
    cout << ans << endl;
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