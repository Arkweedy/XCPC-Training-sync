#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.07 20:03

void solve()
{
    int n, k;
    cin >> n >> k;
    int ans = 0;
    for(int i = 1;i <= n;i++){
        int x = i;
        int ds = 0;
        while(x){
            ds += x % 10;
            x /= 10;
        }
        if(ds == k)ans++;
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