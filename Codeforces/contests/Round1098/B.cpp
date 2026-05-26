#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.05.16 22:40

void solve()
{
    int n ,x, y, k;
    cin >> n >> x >> y >> k;
    x--,y--;

    if(n == 2 || n == 3){
        cout << 1 << endl;
        return;
    }
    else{
        int ans = min((x - y + n) % n, (y - x + n) % n) + k;
        cout << ans << endl;
        return;
    }
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