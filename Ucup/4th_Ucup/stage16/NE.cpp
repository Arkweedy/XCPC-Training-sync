#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

constexpr int mod = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<ll>f(n + 1), g(n + 1), h(n + 1);
    f[0] = g[0] = s[0] - '0';
    h[0] = 1;
    ll mi = 1;
    for(int i=1;i<n;i++){
        ll x = s[i] - '0';
        f[i] = 3 * f[i-1] % mod + mi * x + g[i-1] * x % mod - g[i-1] + 9 * g[i-1] % mod + x * h[i-1]%mod;
        g[i] = mi * x % mod + g[i-1] * x % mod + x * h[i-1] % mod + 10 * g[i-1] % mod;
        h[i] = mi + h[i-1] + g[i-1];
        f[i] %= mod,g[i] %=mod,h[i] %= mod;
        mi = mi * 3 % mod;
    }

    cout<<f[n-1]<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}