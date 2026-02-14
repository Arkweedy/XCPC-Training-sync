#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.11 22:49

void solve()
{
    i64 a, b;
    cin >> a >> b;
    i64 k = 3 * a - 2 * b;
    if(k < 0 || k >= a || k >= b){
        cout << "Alice" << endl;
    }
    else{
        cout << "Bob" << endl;
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