#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.05.09 19:18

void solve()
{
    int n, x;
    cin >> n >> x;
    int mask = 0;
    for(int i = 0;i < n;i++){
        int e;
        cin >> e;
        if((e & x) == e){
            mask |= e;
        }
    }
    if((mask & x) == x){
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