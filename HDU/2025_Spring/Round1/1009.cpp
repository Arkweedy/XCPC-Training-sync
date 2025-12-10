#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, m;
    cin>>n>>m;
    vector<int>a(n);
    vector<int>pa(n + 1);
    //vector<int>aa(n + 1),oa(n + 1);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        pa[i + 1] = pa[i] ^ a[i];
        // aa[i + 1] = aa[i] & a[i];
        // oa[i + 1] = oa[i] | a[i];
    } 
    int len = 1 << m;
    constexpr int inf = 1145141919;
    constexpr ll INF = 1145141919810111;
    vector<int>g(len);
    for(int i = 0;i < len;i++){
        cin>>g[i];
    }
    vector<array<ll,5>>dp;//l, r, and, or, maxval
    vector<ll>val(n, -INF);
    for(int i = 0;i < n;i++){
        ll ma = -INF;
        ll pre = i == 0 ? 0 : val[i - 1];
        dp.push_back({i,i,a[i],0,pre});
        for(auto& arr : dp){
            arr[2]&=a[i];
            arr[3]|=a[i];
            ma = max(ma, arr[4] + g[arr[2] ^ arr[3]]);
        }
        val[i] = ma;
        
        //merge
        dp.push_back({0,0,-1,-1,0});
        vector<array<ll,5>>ndp;
        int l =0;
        ll up = -INF;
        for(int i = 0;i < dp.size();i++){
            if(dp[l][2] == dp[i][2] && dp[l][3] == dp[i][3]){
                up = max(up,dp[i][4]);
            }else{
                ndp.push_back({dp[l][0],dp[i - 1][1],dp[l][2],dp[l][3],up});
                l = i;
                up = dp[i][4];
            }
        }
        dp = ndp;
        // while(dp.size() >= 2){
        //     int p = dp.size() - 1;
        //     if(dp[p][2] == dp[p-1][2] && dp[p][3] == dp[p-1][3]){
        //         dp[p-1][1] = dp[p][1];
        //         dp[p-1][4] = max(dp[p-1][4],dp[p][4]);
        //         dp.pop_back();
        //         // array<ll,5>arr = {dp[p-1][0],dp[p][1],dp[p][2],dp[p][3], max(dp[p][4],dp[p-1][4])};
        //         // dp.pop_back();
        //         // dp.pop_back();
        //         // dp.push_back(arr);
        //     }else{
        //         break;
        //     }
        // }
        
    }
    cout<<val[n-1]<<endl;
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