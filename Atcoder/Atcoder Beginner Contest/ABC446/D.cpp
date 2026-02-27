#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.21 20:14

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    map<int,int>mp;
    for(int i = 0;i < n;i++){
        int v = a[i];
        mp[v] = max(mp[v], mp[v - 1] + 1);
    }
    int ans = 0;
    for(auto [x, c] : mp){
        ans = max(ans, c);
    }
    cout << ans << endl;
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