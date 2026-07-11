#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.06.18 23:16

void solve()
{
    int n;
    cin >> n;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n - 1;i++){
        if(a[i] > a[i + 1]){
            a[i + 1] += a[i];
        }
    }
    i64 ans = a[n - 1];
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