#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//I.cpp Create time : 2026.02.21 18:43

void solve()
{
    string s;
    cin >> s;
    int n = s.length();
    map<char, int>mp;
    for(auto  c : s){
        mp[c]++;
    }
    int ans = s.length();
    for(auto [x, c] : mp){
        ans = min(ans, n - c);
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