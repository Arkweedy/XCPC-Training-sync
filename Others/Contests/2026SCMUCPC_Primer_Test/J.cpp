#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//J.cpp Create time : 2026.05.09 20:37

// 看错题了，不过好像可以出一个新的题，使用类似前缀线性基的科技？
// 对一个集合S，找出最大子集T 使得 T内元素的xor 为 k
// 或许还能对多个k询问？

void solve()
{
    i64 n;
    cin >> n;
    if(n == 1){
        cout << 2 << endl;
    }
    else if(n % 4 == 0){
        cout << n + 1 << endl;
    }
    else{
        cout << n << endl;
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