#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    constexpr int N = 32769;
    int n;
    cin>>n;
    vector<pair<int,int>>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i].first>>a[i].second;//[)
    }
    sort(a.begin(),a.end());
    vector<int>dp(N);
    int p = 1;
    for(int i = 0;i < n;i++){
        while(p <= a[i].first){
            dp[p] = max(dp[p],dp[p - 1]);
            p++;
        }
        dp[a[i].second] = max(dp[a[i].second],dp[a[i].first] + 1);
    }
    while(p < N){
        dp[p] = max(dp[p],dp[p - 1]);
        p++;
    }
    cout<<dp[N - 1]<<endl;
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