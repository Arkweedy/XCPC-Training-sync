#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 17:08:24

int digit(i64 x)
{
    int res = 0;
    while(x != 0){
        x /= 2;
        res++;
    }
    return res;
}




void solve()
{
    i64 x, y, k;
    cin >> x >> y >> k;
    i64 dif = x ^ y;
    i64 dk = digit(k);
    i64 b = 1ll << dk;

    auto atob = [&](i64 a, i64 b)->int // in k
    {
        if(a == b)return 0;
        if((a ^ b) <= k || abs(a - b) == 1)return 1;
        else return 2;
    };


    if(dif < b){
        cout << atob(x, y) << "\n";
    }
    else{
        i64 ans = 0;
        i64 cnt = abs((y >> dk) - (x >> dk));
        if(y < x){
            int ca = atob(x & ((1ll << dk) - 1), 0);
            int cb = atob((1ll << dk) - 1, 0);
            int cc = atob((1ll << dk) - 1, y & ((1ll << dk) - 1));
            ans = cnt + ca + (cnt - 1) * cb + cc;
        }
        else{
            int ca = atob(x & ((1ll << dk) - 1), (1ll << dk) - 1);
            int cb = atob(0, (1ll << dk) - 1);
            int cc = atob((0), y & ((1ll << dk) - 1));
            //cerr << dk << " " << cnt << " " << ca << " " << cb << " " << cc << endl;
            ans = cnt + ca + (cnt - 1) * cb + cc;
        }
        cout << ans << "\n";
    }
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