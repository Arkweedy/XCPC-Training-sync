#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 19:41:58
constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin>>n;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<array<ll, 2>>dp(n + 1);
    vector<ll>cnt(n + 1);
    cnt[0] = 1;
    dp[0][0] = 1;
    for(int i = 1;i < n;i++){
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % P;
        dp[i][1] = dp[i - 1][0];
        cnt[i] = (dp[i][0] + dp[i][1]) % P;
    }

    ll ans = 0;
    for(int i = 0;i < n;i++){
        int l = max(0, i - 2), r = max(0, n - i - 2);
        int L = max(0, i - 1), R = max(0, n - i - 1);
        if(i)ans -= 1ll * a[i] * cnt[l] % P * cnt[r] % P;
        ans += 1ll * a[i] * cnt[L] % P * cnt[R] % P;
        ans = (ans % P + P) % P;
        cerr<<cnt[l]* cnt[r]<<" "<<cnt[L] * cnt[R]<<endl;
        
    }
    cout<<ans<<endl;
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