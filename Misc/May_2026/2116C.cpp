#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//2116C.cpp Create time : 2026.05.27 00:04
constexpr int N = 5000;

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n),c(N + 1);
    constexpr int inf = 1e8;
    vector<int>dp(N + 1, inf);
    int g = 0;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        a[i] = x;
        c[x]++;
        dp[x] = 0;
        g = gcd(g, x);
    }
    //sort(a.begin(),a.end());
    //a.erase(unique(a.begin(),a.end()), a.end());
    for(int i = N;i >= 1;i--){
        if(dp[i] == inf)continue;
        for(auto x : a){
            int d = gcd(i, x);
            dp[d] = min(dp[d], dp[i] + 1);
        }
    }
    //cerr << g << " " << dp[g] << endl;
    int ans = n - c[g] + max(dp[g] - 1, 0);
    cout << ans << endl;
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