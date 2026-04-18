#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.04.11 21:57:12

void solve()
{
    int N = 1000;
    int t;
    cin >> t;

    vector<string>dp(N);
    for(int i = 0;i < N;i++){
        if(dp[i].empty() && i != 0)continue;
        for(int j = 0;j + i + 'a'< N && j < 26;j++){
            dp[i + j + 'a'] = dp[i] + char(j + 'a');
        }
    }

    while(t--){
        int n;
        cin >> n;
        if(n < N){
            if(dp[n].empty()){
                cout << "No" << endl;
            }
            else{
                cout << "Yes" << endl;
                cout << dp[n] << endl;
            }
        }
        else{
            cout << "Yes" << endl;
            int c = (n - N + 'a' - 1) / 'a';
            string res(c, 'a');
            n -= c * 'a';
            res += dp[n];
            cout << res << endl;
        }
    }
    
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