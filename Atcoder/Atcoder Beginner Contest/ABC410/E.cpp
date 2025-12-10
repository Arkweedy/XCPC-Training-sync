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
    int h,m;
    cin>>h>>m;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i]>>b[i];
    }
    constexpr int inf = 1e7;
    vector<int>dp(h + 1, inf);
    dp[0] = 0;
    int ans = 0;
    for(int i = 0;i < n;i++){
        vector<int>ndp(h + 1, inf);
        for(int j = 0;j <= h;j++){
            ndp[j] = min(ndp[j],dp[j] + b[i]);
        }
        for(int j = 0;j + a[i] <= h; j++){
            ndp[j + a[i]] = min(ndp[j + a[i]], dp[j]);
        }
        dp = move(ndp);
        for(int j = 0;j <= h;j++){
            if(dp[j] <= m){
                ans = i + 1;
                break;
            }
        }
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