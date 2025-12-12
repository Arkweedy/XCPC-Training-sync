#include<bits/stdc++.h>

using namespace std;
using ll = long long;

void solve()
{
    int n, d, l;
    cin >> n >> d >> l;
    int dis = l - n;
    int x = dis / d;
    int rem = dis % d;
    //cerr << x << " " << rem << endl;
    int ans2 = 1ll * n * x;
    if(x == 0)ans2 += max(rem - (d - n), 1);
    else{
        if(rem != 0)ans2 += max(1, rem - (d - n));
    }
    ll ans1 = 1ll * n * (l - n - 1) + 1;
    cout << ans2 << " " << ans1 << "\n";
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt ;
    while(tt--){
        solve();
    }
    return 0;
}