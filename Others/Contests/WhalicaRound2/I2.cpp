#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//I2.cpp Create time : 2026.04.08 13:36

constexpr i64 MOD = 998244353;

void solve()
{
    i64 x;
    cin >> x;

    i64 best_p = 0;
    i64 best_q = 1;
    i64 best_sum = 1;

    if(x != 0){
        best_p = x;
        best_q = 1;
        best_sum = best_p + best_q;

        for(i64 q = 2; q < MOD && q < best_sum; q++){
            i64 p = q * x % MOD;
            if(p + q < best_sum){
                best_sum = p + q;
                best_p = p;
                best_q = q;
            }
        }
    }

    cout << best_p << ' ' << best_q << '\n';
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
