#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.16 22:42:40

void solve()
{
    i64 a, b, c, m;
    cin >> a >> b >> c >> m;
    i64 x = 0, y = 0, z = 0;
    x += m / a * 6;
    y += m / b * 6;
    z += m / c * 6;
    {
        i64 lc = lcm(a, b);
        i64 k = m / lc;
        x -= k * 6;
        x += k * 3;
        y -= k * 6;
        y += k * 3;
    }
    {
        i64 lc = lcm(a, c);
        i64 k = m / lc;
        x -= k * 6;
        x += k * 3;
        z -= k * 6;
        z += k * 3;
    }
    {
        i64 lc = lcm(b, c);
        i64 k = m / lc;
        z -= k * 6;
        z += k * 3;
        y -= k * 6;
        y += k * 3;
    }
    {
        i64 lc = lcm(a, lcm(b, c));
        i64 k = m / lc;
        x += k * 2;
        y += k * 2;
        z += k * 2;
    }
    cout << x << " " << y << " " << z << endl;
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