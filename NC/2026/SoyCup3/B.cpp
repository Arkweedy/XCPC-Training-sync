#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.23 15:12:29

constexpr int P = 998244353;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(n * 2 + 1), b(m);
    int ok = 1;
    for(int i = 0;i < m;i++){
        cin >> b[i];
        if(b[i] >= n * 2)ok = 0;
        else a[b[i]] = 1;
    }
    if(!ok){
        cout << 0 << endl;
        return;
    }
    vector<int>dp(n + 1);
    dp[0] = 1;
    for(int i = 1;i <= n * 2;i++){
        vector<int>ndp(n + 1);
        if(a[i] == 1){ // x
            for(int j = 1;j <= min(i, 2 * n - i);j++){
                ndp[j] = dp[j - 1];
            }
        }
        else{ // x + x^-1 , > 0
            for(int j = 0;j <= min(i, 2 * n - i);j++){
                if(j > 0)ndp[j] += dp[j - 1];
                if(j < n)ndp[j] += dp[j + 1];
                if(ndp[j] >= P)ndp[j] -= P;
            }
        }
        dp = move(ndp);
    }
    int ans = dp[0];
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