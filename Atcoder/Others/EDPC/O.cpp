#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.10 11:22:54

constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>a(n, vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> a[i][j];
        }
    }
    int len = 1 << n;
    vector<int>dp(1 << n);
    dp[len - 1] = 1;
    for(int i = 0;i < n;i++){
        vector<int>ndp(1 << n);
        for(int j = 0;j < n;j++){
            if(a[i][j]){
                for(int k = 0;k < len;k++){
                    if((k >> j) & 1){
                        ndp[k ^ (1 << j)] = (ndp[k ^ (1 << j)] + dp[k]) % P;
                    }
                }
            }
        }
        dp = move(ndp);
    }
    cout << dp[0] << endl;
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