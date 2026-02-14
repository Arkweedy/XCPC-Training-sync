#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.02.11 22:35

int digit(int x)
{
    int res = 0;
    while(x){
        res += x % 10;
        x /= 10;
    }
    return res;
}

void solve()
{
    int x;
    cin >> x;
    int ans = 0;
    for(int i = 0;i <= 200;i++){
        int y = x + i;
        if(y - digit(y) == x){
            ans++;
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}