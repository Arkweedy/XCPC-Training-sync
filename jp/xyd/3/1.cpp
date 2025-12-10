#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    vector<ll>dp(n + 1);
    for(int i = 1;i <= n;i++){
        dp[i] = max((ll)a[i], a[i] + dp[i - 1]);
    }
    ll ans = -1145141919;
    for(int i = 1;i <= n;i++){
        ans = max(ans, dp[i]);
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