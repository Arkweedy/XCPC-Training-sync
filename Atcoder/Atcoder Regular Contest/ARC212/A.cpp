#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//A.cpp Create time : 2026.01.11 20:13

// 3 pairs

constexpr int P = 998244353;

void solve()
{
    int k;
    cin >> k;
    i64 ans = 0;
    
    for(int i = 2;i <= k - 4;i++){
        for(int j = i;i + j <= k - 2;j++){
            if(k - i - j < j)continue;
            i64 res = 1ll * (k - max({i, j, k - i - j})) * (i - 1) * (j - 1) * (k - i - j - 1);
            if(i == j && i == k - i - j);
            else if(i == j || i == k - i - j || j == k - i - j)res *= 3;
            else res *= 6;
            ans += res;
            ans %= P;
        }
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