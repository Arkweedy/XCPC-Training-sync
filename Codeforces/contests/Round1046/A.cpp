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
    vector<int>a(n);
    map<int,vector<int>>mp;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        mp[a[i]].push_back(i);
    }

    vector<int>next(n + 1, -1);
    for(auto [x , arr] : mp){
        for(int i = 0;i + x - 1 < (int)arr.size();i++){
            //cerr<<i + x - 1<<endl;
            next[arr[i]] = arr[i + x - 1] + 1;
        }
    }

    // for(int i = 0;i < n;i++){
    //     cerr<<next[i]<<" ";
    // }
    // cerr<<endl;

    vector<int>dp(n + 1);
    for(int i = 0;i < n;i++){
        if(i > 0)dp[i] = max(dp[i],dp[i - 1]);
        if(next[i] != -1){
            dp[next[i]] = max(dp[next[i]], dp[i] + a[i]);
        }
    }

    // for(int i = 0;i <= n;i++){
    //     cerr<<dp[i]<<" ";
    // }
    // cerr<<endl;

    int ans = 0;
    for(int i = 0;i <= n;i++){
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}