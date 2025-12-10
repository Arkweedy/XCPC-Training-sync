#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//dp[i][j][k][01]
// 1 ~ i
// diff = j
// k >= j
// exist j

//i,j,k,0 -> 
//choose exist i + 1, j, k <- .. * j
//
//choose no exist 
//  exist j + 1 -> * (n - j)
//  no exist j + 1 -> (n - j - 1)
//

//i,j,k,1
//choose exist <- *j
//choose no exist
// exist j + 1 -> *(n - j)
// no exist j + 1 ->(n - j - 1)

int dp[301][301][301][2];

void solve()
{
    int n, p;
    cin>>n>>p;
    dp[0][0][0][0] = 1;
    for(int i = 0;i < n;i++){
        for(int j = 0;j <= i;j++){
            for(int k = 0;k <= j;k++){
                //dp[0]
                //exist
                dp[i + 1][j][k][0] = (dp[i + 1][j][k][0] + 1ll * dp[i][j][k][0] * j % p) % p;
                dp[i + 1][j][k][1] = (dp[i + 1][j][k][1] + 1ll * dp[i][j][k][1] * (j - 1) % p) % p;
                //new
                //calc j + 1
                int per = binom()

                dp[i + 1][j + 1][k][0] = (dp[i + 1][j + 1][k][0] + )
            }
        }
    }
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