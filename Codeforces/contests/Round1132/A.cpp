#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.11.06 22:36

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    i64 x = 0, y = 0;
    sort(a.begin(),a.end());
    for(int i = n - 1;i >= 0;i--){
        if(x < y){
            x += 1 << a[i];
        }
        else{
            y += 1 << a[i];
        }
    }
    i64 ans = x * y;
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