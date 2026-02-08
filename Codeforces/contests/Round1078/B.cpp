#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.08 17:14

void solve()
{
    int n, x, y;
    cin >> n >> x >> y;
    vector<int>a(n);
    i64 sum = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i] / x * y;
    }
    sort(a.begin(),a.end());

    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans = max(ans, sum - (a[i] / x * y) + a[i]);
    }
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