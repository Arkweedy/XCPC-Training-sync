#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.05.09 19:05

void solve()
{
    string s;
    cin >> s;
    string t = "SCMU";
    int ans = 0;
    for(int i = 0;i + 4 <= s.length();i++){
        if(t == s.substr(i, 4)){
            ans++;
        }
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