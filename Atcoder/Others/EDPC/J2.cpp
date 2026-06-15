#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.15 17:16:22

using ld = long double;

void solve()
{
    int n;
    cin >> n;
    vector<int>c(4);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x]++;
    }
    int x = c[1], y = c[2], z = c[3];
    vector<vector<vector<ld>>>dp(n + 1, vector<vector<ld>>(y + z + 1, vector<ld>(z + 1, 0)));
    for(int k = 0;k <= z;k++){
        for(int j = 0;j <= y + z - k;j++){
            for(int i = 0;i <= n - j - k;i++){
                ld val = n;
                int sum = i + j + k;
                if(sum == 0)continue;
                if(i > 0)val += dp[i - 1][j][k] * i;
                if(j > 0)val += dp[i + 1][j - 1][k] * j;
                if(k > 0)val += dp[i][j + 1][k - 1] * k;
                val /= sum;
                dp[i][j][k] = val;
            }
        }
    }
    ld ans = dp[x][y][z];
    cout << fixed << setprecision(10) << ans << endl;
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