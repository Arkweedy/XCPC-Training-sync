#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.07.29 13:01

void solve()
{
    int p;
    cin >> p;
    int q = p + 1, x1 = p, x2 = 1;
    // ap + b -> (b - a)(ap + b) = p -> (ba -a*a - 1) = 0 , a = b or b = 0 -> a*a = -1 mod p + 1 -> a*a = p
    cout << p * p % (p + 1) << endl;
    
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