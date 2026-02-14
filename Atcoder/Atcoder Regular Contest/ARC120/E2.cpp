#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E2.cpp Create time : 2026.02.12 21:51

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n + 2);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    a[0] = a[1];
    a[n + 1] = a[n];
    constexpr int inf = 1e9;
    vector<int>f(n + 1, inf);
    f[0] = 0;
    //f[1] = 0;
    for(int i = 2;i <= n;i++){
        if(i >= 2){
            f[i] = min(f[i], max(f[i - 2] , (a[i + 1] - a[i - 2]) / 2));
        }
        if(i >= 3){
            f[i] = min(f[i], max(f[i - 3] , (a[i + 1] - a[i - 3]) / 2));
        }
    }
    cout << f[n] << endl;
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