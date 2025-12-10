#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 998244353;

void solve()
{
    constexpr int m = 10;
    vector<int>prime = {2,3,5,7,11,13,17,19,23,29};
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>mask(n);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            int x = a[i];
            while(x % prime[j] == 0){
                x /= prime[j];
                mask[i] ^= (1 << j);
            }
        }
    }

    int len = 1 << m;
    vector<int>dp(len);//dp[x] x 的 第i位 -> prime[i] 的奇偶性 
    dp[0] = 1;
    for(int i = 0;i < n;i++){
        auto ndp = dp;
        for(int j = 0;j < len;j++){
            ndp[j ^ mask[i]] = (ndp[j ^ mask[i]] + dp[j]) % P;
        }
        dp = ndp;
    }

    cout<<dp[0]<<endl;
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