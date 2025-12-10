#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    string s;
    cin>>s;
    int n = s.length();
    s = ' ' + s;
    constexpr int inf = 114514;
    vector<array<int,3>>dp(n + 1, array<int,3>{inf, inf, inf});
    dp[0][0] = 0;
    int tr0[3][3] = {0,inf,inf,inf,1,0,inf,0,0}, tr1[3][3] = {1,0,inf,inf,0,inf,inf,inf,1};
    for(int i = 1;i <= n;i++){
        if(s[i] == '0'){
            for(int j = 0;j < 3;j++){
                for(int k = j;k < 3;k++){
                    dp[i][k] = min(dp[i][k], dp[i - 1][j] + tr0[j][k]);
                }
            }
        }
        else{
            for(int j = 0;j < 3;j++){
                for(int k = j;k < 3;k++){
                    dp[i][k] = min(dp[i][k], dp[i - 1][j] + tr1[j][k]);
                }
            }
        }
    }
    int ans = min({dp[n][0],dp[n][1],dp[n][2]});
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