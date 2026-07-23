#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.22 14:30:31

constexpr int P = 998244353;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int inv(int a)
{
    return power(a, P - 2);
}

void solve()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    int p = 1ll * x * inv(y) % P;
    if(n > m){
        swap(n, m);
        p = (P + 1 - p) % P;
    }
    n--,m--;
    int q = (1 - p + P) % P;
    int ans = 4 * n + 2;
    int remp = 1;
    int pr = power(q, n); //\binom{n + k}{k} = \frac{(n + 1)^{^k}}{k!} p^k q^n
    int cost = (3 - p + P) % P;
    for(int k = 0;k < m - n;k++){
        int rem = m - n - k;
        ans = (ans + 1ll * pr * rem % P * cost % P) % P;
        remp = (remp - pr + P) % P;
        pr = 1ll * pr * (n + k + 1) % P * inv(k + 1) % P * p % P;
    }
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