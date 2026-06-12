#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.06.09 22:34

void solve()
{
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    int t = (n + x + y - 1) / (x + y);
    t = min(t, (n - x * z + x + 10 * y - 1) / (x + 10 * y) + z);
    cout << t << endl;
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