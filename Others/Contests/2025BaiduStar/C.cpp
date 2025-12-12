#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n), b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
    }

    ll ans = 0;
    auto get = [&](int x)->int
    {
        const int N = n * 100;
        vector<vector<int>>dp(N + 1, vector<int>(n + 1));
        dp[0][0] = 1;
        for(int i = 0;i < n;i++){
            if(i == x)continue;
            for(int j = N;j - b[i] >= 0;j--){
                for(int k = 0;k < n;k++){
                    dp[j][k + 1] = (dp[j][k + 1] + dp[j - b[i]][k]) % P;
                }
            }
        }

        vector<int>fac(n + 1);
        fac[0] = 1;
        for(int i = 1;i <= n;i++){
            fac[i] = 1ll * fac[i - 1] * i % P;
        }

        // for(int i = 0;i <= 6;i++){
        //     for(int j = 0;j <= 3;j++){
        //         cerr << dp[i][j] << " ";
        //     }
        //     cerr << endl;
        // }

        ll ans = 0;
        if(a[x] > N)return 0;
        for(int j = 0;j < n;j++){//0 ~ n-1 
            ans = (ans + 1ll * dp[a[x]][j] * fac[n - j - 1] * fac[j]) % P;
            
        }
        return ans;
    };
    for(int i = 0;i < n;i++){
        ans += get(i);
    }
    ans %= P;
    cout << ans << endl;

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt ;
    while(tt--){
        solve();
    }
    return 0;
}