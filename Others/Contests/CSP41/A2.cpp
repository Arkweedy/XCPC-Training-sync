#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A2.cpp Create time : 2026.04.02 20:35

void solve()
{
    int n;
    cin >> n;
    auto check = [&](int x)->int
    {   
        int o = 0, z = 0;
        while(x != 0){
            if(x % 2 == 0){
                z++;
            }
            else{
                o++;
            }
            x /= 2;
        }
        return o == z;
    };

    int ans = 0;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        ans += check(x);
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