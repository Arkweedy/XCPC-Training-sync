#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.05.18 22:35

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;
    i64 ans = 0;
    ans += 1ll * n / 3 * min(a * 3, b);
    if(n % 3 != 0){
        ans += min(b, n % 3 * a);
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