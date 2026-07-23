#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.17 15:30:57

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
    if(a <= 0)return 1;
    return power(a, P - 2);
}

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    vector<int>prod(n + 1);
    prod[0] = 1;
    for(int i = 1;i <= n;i++){
        prod[i] = 1ll * prod[i - 1] * a[i] % P;
    }

    auto get = [&](int k)->int
    {
        return k / 2;
    };

    i64 ans = 0;
    for(int i = n - 1;i >= 0;i--){
        int dim = n - i;
        int coef = 1ll * get(dim) * prod[i] % P;
        int coef2 = 1ll * (power(a[i + 1], dim - 1) - power(a[i], dim - 1) + P) % P * inv(dim - 1) % P;
        ans += 1ll * coef2 * coef % P;
    }
    ans = (ans % P + P) % P;
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