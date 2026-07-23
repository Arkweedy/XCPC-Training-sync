#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.23 14:48:34

void solve()
{
    constexpr int N = 4e5;
    int a, b , c;
    cin >> a >> b >> c;
    string s(N, '1');
    string t = "9" + string(b - 1, '0');
    string t1(N - b, '0'), t2(N - b, '9');
    t1 = t + t1;
    t2 = t + t2;
    cout << s << " " << t1 << " " << s << " " << t2 << endl;
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