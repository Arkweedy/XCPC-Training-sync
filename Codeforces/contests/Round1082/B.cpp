#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.23 22:43

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = ' ' + s;
    vector<array<int,3>>dp(n + 1, array<int,3>{});
    // 0 ab 1 aa 2 bb
    if(n % 2 == 0){//ab
        dp[0][0] = 1;
    }
    else{
        dp[0][1] = 1;
    }

    for(int i = 1;i <= n;i++){
        if(s[i] == 'a'){// aa -> ab / ab -> bb
            dp[i][0] |= dp[i - 1][1];
            dp[i][2] |= dp[i - 1][0];
        }
        else if(s[i] == 'b'){ // ab -> aa / bb -> ab
            dp[i][0] |= dp[i - 1][2];
            dp[i][1] |= dp[i - 1][0];
        }
        else{// ?
            dp[i][0] |= dp[i - 1][1];
            dp[i][2] |= dp[i - 1][0];
            dp[i][0] |= dp[i - 1][2];
            dp[i][1] |= dp[i - 1][0];
        }
    }

    int ans = 0;
    if(dp[n][0] || dp[n][1] || dp[n][2]){
        ans = 1;
    }
    if(ans){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
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