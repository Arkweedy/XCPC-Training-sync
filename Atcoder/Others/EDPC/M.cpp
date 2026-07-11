#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.10 10:36:31

constexpr int P = 1e9 + 7;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>dp(k + 1);
    vector<int>pdp(k + 1, 1);
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        int x = a[i];
        for(int j = k;j >= 0;j--){
            dp[j] = (pdp[j] - (j - x > 0 ? pdp[j - x - 1] : 0) + P) % P;
        }
        pdp[0] = dp[0];
        for(int j = 1;j <= k;j++){
            pdp[j] = (pdp[j - 1] + dp[j]) % P;
        }
    }
    cout << dp[k] << endl;
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