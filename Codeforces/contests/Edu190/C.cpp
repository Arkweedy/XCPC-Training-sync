#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.05.18 23:01

void solve()
{
    int n;
    cin >> n;
    i64 ans = 0;
    i64 in = 0;
    i64 alone = 0;
    i64 cnt = 0;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        if(x >= 2){
            ans += x;
            in += x / 2 - 1;
            cnt++;
        }
        else{
            alone++;
        }
    }
    if(cnt == 1)in++;
    ans += min(alone, in);
    if(ans <= 2)ans = 0;
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