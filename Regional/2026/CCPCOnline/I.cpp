#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;

void solve()
{
    i64 n;
    cin >> n;
    i64 a = 1, b = -1, c = n / 2;
    if(n % 2 == 0){
        cout << a << " " << b << " " << c << "\n";
    }
    else{
        cout << -1 << "\n";
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}

