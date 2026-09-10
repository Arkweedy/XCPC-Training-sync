#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.07.16 22:41

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int m = s.length();
    if(k * 2 <= m){
        int ans = 0;
        for(int i = 0;i < k;i++){
            if(s[i] == 'L')ans++;
            if(s[m - i - 1] == 'R')ans++;
        }
        cout << ans << endl;
    }
    else{
        cout << -1 << endl;
    }
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