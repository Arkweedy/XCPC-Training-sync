#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.12 15:25:37

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
    int a, b;
    cin >> a >> b;
    int x, y;
    int g = exgcd(a,b,x,y);
    assert(g == 1);
    x = (x % b + b) % b;
    cout << x << endl;
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