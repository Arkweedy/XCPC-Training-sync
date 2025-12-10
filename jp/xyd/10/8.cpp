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
    vector<ll>dp(n + 1);
    if(n == 2 || n == 3){
        cout<<n-1<<endl;
        return;
    }
    dp[0] = dp[1] = 1;
    for(int i = 0;i <= n;i++){
        for(int j = 2;j + i <= n;j++){
            dp[i + j] = max(dp[i + j], dp[i] * j);
        }
    }
    cout<<dp[n]<<endl;
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