#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.16 15:10:18

constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int>dp = {1};
    for(int i = 0;i < n - 1;i++){
        int c = i + 1;
        vector<int>pdp(c + 1),sdp(c + 1);
        for(int j = 0;j < c;j++){
            if(s[i] == '>'){
                sdp[j] = dp[j];
            }
            else{
                pdp[j + 1] = dp[j];
            }
        }
        for(int j = 1;j < c + 1;j++){
            pdp[j] = (pdp[j] + pdp[j - 1]) % P;
        }
        for(int j = c - 1;j >= 0;j--){
            sdp[j] = (sdp[j] + sdp[j + 1]) % P;
        }
        vector<int>ndp(c + 1);
        for(int j = 0;j < c + 1;j++){
            ndp[j] = (pdp[j] + sdp[j]) % P;
        }
        dp = move(ndp);
    }
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans += dp[i];
    }
    ans %= P;
    cout << ans << endl;
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