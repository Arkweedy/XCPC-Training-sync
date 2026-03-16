#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.03.14 23:01

void solve()
{
    int n;
    cin >> n;
    vector<int>c(n), p(n);
    for(int i = 0;i < n;i++){
        cin >> c[i] >> p[i];
    }
    double ans = 0;
    for(int i = n - 1;i >= 0;i--){
        ans = max(ans, ans * (100 - p[i]) / 100 + c[i]);
    }
    cout << fixed << setprecision(10) << ans << endl;
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