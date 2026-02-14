#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.02.14 20:04

void solve()
{
    int n;
    cin >> n;
    vector<string>s(n);
    int m = 0;
    for(int i = 0;i < n;i++){
        cin >> s[i];
        m = max(m, (int)s[i].length());
    }

    for(int i = 0;i < n;i++){
        int k = m - s[i].length();
        cout << string(k / 2, '.') << s[i] << string(k / 2, '.') << endl;
    }
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