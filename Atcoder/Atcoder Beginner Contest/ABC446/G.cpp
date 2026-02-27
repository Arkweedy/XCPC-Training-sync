#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.02.21 20:51

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n + 1);
    vector<vector<int>>p(n + 1);
    vector<int>rk(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        p[a[i]].push_back(i);
        rk[i] = p[a[i]].size() - 1;
    }

    vector<i64>end(n + 1); // can not end with v -> self / already
    vector<i64>dp(n + 1);// end with a_i
    i64 all = 1;
    dp[0] = 1;
    end[0] = 1;
    for(int i = 1;i <= n;i++){
        int v = a[i];
        if(rk[i] + v - 1 < p[v].size()){
            //cerr << p[v][rk[i] + v - 1] << endl;
            dp[p[v][rk[i] + v - 1]] = (dp[p[v][rk[i] + v - 1]] + (1ll * all - end[v] + P) % P + P) % P;
        }
        end[v] = (dp[i] + all) % P;
        all = (all + dp[i]) % P;
    }

    i64 ans = 0;
    for(int i = 1;i <= n;i++){
        ans = (ans + dp[i]) % P;
    }
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