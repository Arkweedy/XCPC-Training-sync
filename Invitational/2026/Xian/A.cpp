#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.05.02 15:46:04

void solve()
{
    int n;
    cin >> n;
    vector<i64>a(n);
    i64 sum = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    if(sum % n != 0){
        cout << -1 << endl;
        return;
    }
    i64 ave = sum / n;
    for(int i = 0;i < n;i++){
        a[i] -= ave;
    }
    i64 ans = 0;
    for(int i = 0;i < n - 1;i++){
        if(a[i] > 0){
            cout << -1 << endl;
            return;
        }
        a[i + 1] += a[i];
        ans += max(-a[i] + (i >= 2 ? a[i - 2] : 0ll), 0ll);
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