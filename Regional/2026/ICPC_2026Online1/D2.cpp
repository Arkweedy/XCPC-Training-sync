#include <bits/stdc++.h>
using ll = long long;
using i64 = long long;
using namespace std;

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<int>c(n);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x]++;
    }
    int mi = 0, ma = 0;
    int ans = 1;
    for(int i = 0;i < n;i++){
        if(mi == ma)ans = 1ll * ans * 2 % P;
        if(c[mi] == 0){
            c[ma]--;
            mi++;
        }
        else{
            c[mi]--;
            ma++;
        }
    }
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}