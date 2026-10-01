#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//900D.cpp Create time : 2026.09.26 09:19
constexpr int P = 1e9 + 7;
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

void solve()
{
    int x, y;
    cin >> x >> y;
    if(y % x != 0){
        cout << 0 << endl;
        return;
    }
    int n = y / x;
    int nn = n;
    vector<pair<int,int>>facs;
    for(int i = 2;i * i <= n;i++){
        if(n % i == 0){
            int c = 0;
            while(n % i == 0){
                n /= i;
                c++;
            }
            facs.emplace_back(i, c);
        }
    }
    if(n != 1)facs.emplace_back(n, 1);

    i64 ans = 0;
    int m = facs.size();
    n = nn;
    auto dfs = [&](auto&&self, int x, int mu, int p)->void
    {
        if(p == m){
            ans = (ans + mu * power(2, n / x - 1) + P) % P;
            return;
        }
        auto [q, c] = facs[p];
        self(self, x, mu, p + 1);
        self(self, x * q, -mu, p + 1);
        return;
    };
    dfs(dfs, 1, 1, 0);
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