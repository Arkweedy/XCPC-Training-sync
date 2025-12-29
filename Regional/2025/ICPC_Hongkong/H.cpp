#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.29 13:28:50

void solve()
{
    string s;
    cin >> s;
    int ans = s.length() - 2;
    for(int i = 0;i + 1 < s.length();i++){
        if(s[i] == s[i + 1]){
            ans++;
            break;
        }
    }
    cout << ans << "\n";
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