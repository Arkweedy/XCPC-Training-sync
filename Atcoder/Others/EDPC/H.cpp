#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.15 14:47:33

constexpr int P = 1e9 + 7;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<vector<int>>dp(n, vector<int>(m + 1));
    dp[0][0] = 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(i > 0){
                if(a[i][j] == '.' && a[i - 1][j] == '.'){
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % P;
                }
            }
            if(j > 0){
                if(a[i][j] == '.' && a[i][j - 1] == '.'){
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % P;
                }
            }
        }
    }
    int ans = dp[n - 1][m - 1];
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