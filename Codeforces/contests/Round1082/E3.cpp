#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.24 00:14

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        if(s[i] == '(')a[i] = 1;
        else a[i] = -1;
    }
    vector<int>pa(n);
    pa[0] = a[0];
    for(int i = 1;i < n;i++){
        pa[i] = pa[i - 1] + a[i];
    }

    vector<int>ok(n);
    for(int i = 0;i < n;i++){
        if(pa[i] - a[i] - 1 >= 0)ok[i] = 1;
    }

    vector<int>p2(n + 1);
    p2[0] = 1;
    for(int i = 1;i <= n;i++){
        p2[i] = 1ll * p2[i - 1] * 2 % P;
    }
    i64 ans = 0;
    
    vector<i64>dp(n + 1); //self out, pre ok
    dp[0] = 1;

    for(int i = 0;i < n;i++){
        if(a[i] == 1){
            ans += p2[i];
        }
        else{
            ans += dp[i - 1];
        }
        // chs or not
        
        if(a[i] == 1){
            //chs or not
            dp[i + 1] += 2 * dp[i];
        }
        else{
            if(a[i] <= 1)dp[i + 1] += dp[i];
            else dp[i + 1] = dp[i] * 2;
        }
        ans %= P;
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