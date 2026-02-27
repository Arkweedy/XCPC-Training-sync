#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.26 22:38

void solve()
{
    int n;
    cin >> n;
    int ans = 1;
    for(int i = 2;i * i <= n;i++){
        if(n % i == 0){
            ans *= i;
            while(n % i == 0)n /= i;
        }
    }
    ans *= n;
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