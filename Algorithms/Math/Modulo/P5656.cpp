#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.12 14:46:42

int exgcd(int a, int b, int &x, int &y)
{
    x = 1, y = 0;
    array<int, 4>m = {1, 0, 0 ,1};//matrix
    while(b != 0){
        int c = a / b;
        m = {m[1], m[0] - c * m[1], m[3], m[2] - c * m[3]};
        int t = a % b;
        a = b;
        b = t;
    }
    x = m[0], y = m[2];
    return a;
}

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;
    int x, y;
    int g = exgcd(a, b, x, y);
    if(c % g != 0){
        cout << -1 << "\n";
        return;
    }
    
    ll h = c / g;
    ll x0 = x * h, y0 = y * h;
    ll dx = b / g, dy = a / g;
    ll c1 = ((x0 % dx - dx) % dx + dx - x0) / dx;//c1 lcm
    ll x1 = x0 + dx * c1, y1 = y0 - dy * c1;
    ll c2 = ((y0 % dy - dy) % dy + dy - y0) / dy;//c2 lcm
    ll x2 = x0 - dx * c2, y2 = y0 + dy * c2; 
    ll cnt = (x2 - x1) /dx + 1;
    if(cnt >= 1){
        cout << cnt << " " << x1 << " " << y2 << " " << x2 << " " << y1 << "\n";
    }
    else{
        cout << x1 << " " << y2 << "\n";
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