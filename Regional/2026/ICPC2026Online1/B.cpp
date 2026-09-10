#include <bits/stdc++.h>
using ll = long long;
using i64 = long long;
using namespace std;

constexpr int P = 998244353;

void solve()
{
    int n, v;
    cin >> n >> v;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>dp(v + 1);
    dp[v] = 1;
    for(int i = n - 1;i >= 0;i--){
        vector<int>ndp(v + 1);
        for(int j = v;j >= 0;j--){
            ndp[j] = (ndp[j] + 1ll * dp[j] * i) % P;
            ndp[j % a[i]] = (ndp[j % a[i]] + dp[j]) % P; // mod a[i], fast
        }
        dp = move(ndp);
        // for(int i = 0;i <= v;i++){
        //     cerr << dp[i] <<" ";
        // }
        // cerr << endl;
    }
    for(int i = 0;i <= v;i++){
        cout << dp[i] <<" ";
    }
    cout << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}