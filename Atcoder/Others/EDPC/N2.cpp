#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//N2.cpp Create time : 2026.07.12 02:21

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<i64>pa(n);
    pa[0] = a[0];
    for(int i = 1;i < n;i++){
        pa[i] = pa[i - 1] + a[i];
    }
    auto get = [&](int l, int r)->i64
    {
        if(l == 0)return pa[r];
        else return pa[r] - pa[l - 1];
    };
    constexpr i64 inf = 1e18;
    vector<vector<i64>>dp(n, vector<i64>(n, inf));
    vector<vector<int>>opt(n, vector<int>(n));
    for(int i = 0;i < n;i++){
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    auto calc = [&](int l, int r, int m)->i64
    {
        return dp[l][m] + dp[m + 1][r] + get(l, r);
    };
    for(int i = 2;i <= n;i++){
        for(int l = 0;l < n - i + 1;l++){
            int r = l + i - 1;
            for(int k = opt[l][r - 1]; k < min(r, opt[l + 1][r] + 1); k++){
                if(dp[l][r] >= calc(l, r, k)){
                    dp[l][r] = calc(l, r, k);
                    opt[l][r] = k;
                }
            }
        }
    }
    
    i64 ans = dp[0][n - 1];
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