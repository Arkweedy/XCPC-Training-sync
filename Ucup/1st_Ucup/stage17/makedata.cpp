#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 23:08:17

void solve()
{
    int n = 2e5;
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    cout << n << endl;
    for(int i = 0;i < n;i++){
        cout << g() % 100000000 << " ";
    }
    cout << endl;
    for(int i = 0;i < n - 1;i++ ){
        cout << (g() % 2 == 1 ? '-' : '+');
    }
    cout << endl;
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