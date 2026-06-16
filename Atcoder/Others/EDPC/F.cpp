#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.06.13 17:14

void solve()
{
    string s, t;
    cin >> s >> t;
    int n = s.length(), m = t.length();
    s = ' ' + s;
    t = ' ' + t;
    vector<vector<int>>dp(n + 1, vector<int>(m + 1));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            if(s[i] == t[j])dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
        }
    }
    int len = dp[n][m];
    string res;
    int x = n, y = m;
    while(x != 0 && y != 0){
        if(len == dp[x - 1][y - 1] + 1 && s[x] == t[y]){
            res += s[x];
            x--;
            y--;
            len--;
        }
        else if(len == dp[x - 1][y]){
            x--;
        }
        else{
            y--;
        }
    }
    assert(len == 0);
    reverse(res.begin(), res.end());
    cout << res << endl;
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