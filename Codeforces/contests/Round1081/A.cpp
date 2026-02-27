#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.02.21 22:35

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    char la = '0';
    s += '1';
    int cnt = 1;
    int ma = 1;
    for(int i = 0;i <= n;i++){
        if(s[i] != la){
            ma = max(ma, cnt);
            la = s[i];
            cnt = 0;
            ans++;
        }
        cnt++;
    }
    //cerr << ans << " " << ma << endl;
    ans--;
    if(s[0] != s[n - 1] && ma >= 2){
        ans++;
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