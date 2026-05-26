#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.05.18 22:38

//213
//211111113
//2222222222 111111 33333333

void solve()
{
    string s;
    cin >> s;
    int n = s.length();
    s = " " + s;
    vector<vector<int>>dp(n + 1, vector<int>(2));
    for(int i = 1;i <= n;i++){
        dp[i] = dp[i - 1];
        if(s[i] == '2'){
            dp[i][0]++;
        }
        if(s[i] == '1' || s[i] == '3'){
            dp[i][1] = max(dp[i][0], dp[i][1]) + 1;
        }
    }

    

    int res = max(dp[n][0], dp[n][1]);
    

    cout << n - res << endl;
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