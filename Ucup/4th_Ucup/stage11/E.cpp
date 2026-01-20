#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.20 10:35:36

void solve()
{
    int k;
    cin >> k;
    int n = k * 2 + 1;
    cout << n << endl;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < k;j++){
            cout << (i + j + 1) % n + 1 << " ";
        }
        cout << "\n";
    }
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