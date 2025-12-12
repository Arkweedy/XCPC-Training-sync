#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int P = 1e9 + 7;

constexpr int N = 2e4 + 10;
constexpr int M = 201;
int n;
int sum;
int dp[N][M];
int a[M], b[M];
void add(int i)
{
    for(int j = sum;j - b[i] >= 0;j--){
        for(int k = n - 1;k >= 0;k--){
            dp[j][k + 1] = (dp[j][k + 1] + dp[j - b[i]][k]) % P;
        }
    }
}

void del(int i)
{
    for(int j = b[i];j <= sum;j++){
        for(int k = 0;k < n;k++){
            dp[j][k + 1] = (dp[j][k + 1] - dp[j - b[i]][k] + P) % P;
        }
    }
}


void solve()
{
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
        sum += b[i];
    }
    dp[0][0] = 1;
    for(int i = 0;i < n;i++){
        add(i);
    }

    vector<int>fac(n + 1);
    fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }

    ll ans = 0;
    for(int i = 0;i < n;i++){
        del(i);
        if(a[i] <= N){
            for(int j = 0;j < n;j++){
                ans = (ans + 1ll * dp[a[i]][j] * fac[n - j - 1] % P * fac[j] % P) % P;
            }
        }
        add(i);
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