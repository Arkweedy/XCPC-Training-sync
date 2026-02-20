#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.02.15 15:15

void solve()
{
    string s;
    cin >> s;
    string a = s.substr(1, 2), b = s.substr(3, 2), c = s.substr(5, 2);
    auto calc = [&](string t)->int
    {
        int c = 255;
        c -= 16 * (('0' <= t[0] && t[0] <= '9') ? t[0] - '0' : t[0] - 'a' + 10);
        c -= ('0' <= t[1] && t[1] <= '9') ? t[1] - '0' : t[1] - 'a' + 10;
        return c;
    };
    cout << "#";
    cout << hex << setw(2) << setfill('0') << calc(a);
    cout << hex << setw(2) << setfill('0') << calc(b);
    cout << hex << setw(2) << setfill('0') << calc(c);
    cout << endl;
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