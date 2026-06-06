#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = ' '  + s;
    vector<i64>f(n + 1), g(n + 1),pg(n + 1);
    f[1] = g[1] = pg[1] = s[1] -'0';
    pg[1]++;
    pg[0] = 1;
    i64 p3 = 1;
    for(int i = 2;i <= n;i++){
        i64 x = s[i] - '0';
        f[i] = (f[i - 1] * 3 + p3 * x + (x + 8) * g[i - 1] + x * pg[i - 2]) % P;
        g[i] = (p3 * x + (x + 10) * g[i - 1] + x * pg[i - 2]) % P;
        pg[i] = (pg[i - 1] + g[i] + p3) % P;
        p3 = p3 * 3 % P;
        cerr << f[i] << " " << g[i] << " " << pg[i] << endl;
    }

    cout << f[n] << endl;
    return;
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