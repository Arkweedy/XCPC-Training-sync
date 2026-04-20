#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.04.08 10:32

void solve()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if(gcd(n, a) == 1 && gcd(m, b) == 1 && gcd(n, m) <= 2){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
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