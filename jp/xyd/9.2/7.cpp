#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    double P;
    cin>>P>>n;
    vector<int>a(n);
    vector<double>p(n);
    int sum = 0;
    for(int i = 0;i < n;i++){
        cin>>a[i]>>p[i];
        sum += a[i];

    }
    double neg = 1 - P;
    vector<double>dp(sum + 1, 0);
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        for(int j = sum - a[i];j >= 0;j--){
            dp[j + a[i]] = max(dp[j + a[i]], dp[j] * (1 - p[i]));
        }
    }
    int ans = 0;
    for(int i = 0;i <= sum;i++){
        if(dp[i] > neg)ans = i; 
    }
    cout<<ans<<endl;
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