#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.05.18 23:10

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n), b(n), na1(n, -1), nb1(n, -1), pa1(n, -1), pb1(n, -1);
    vector<int>la(n + 1, n), lb(n + 1, n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
        b[i]--;
    }

    for(int i = n - 1;i >= 0;i--){
        la[a[i]] = i;
        lb[b[i]] = i;
        // na1[i] = la[0];
        // nb1[i] = lb[0];
        pa1[i] = la[a[i] + 1];
        pb1[i] = lb[b[i] + 1];
    }

    vector<int>dp1(n + 1), dp2(n + 1); // dp1 : keep -1, dp2 : same
    vector<int>v(n + 1);
    for(int i = n - 1;i >= 0;i--){
        if(a[i] > 0 && b[i] > 0){
            dp1[i] = dp1[i + 1] + 1;
        }
        else{
            dp1[i] = 0;
        }
        if(a[i] == b[i]){
            int nxta = pa1[i], nxtb = pb1[i];
            if(nxta == nxtb){
                dp2[i] = nxta - i + dp2[nxta];
            }
            else{
                dp2[i] = min(nxta,nxtb) - i;
            }
        }
        if(a[i] == b[i] && a[i] == 0){
            dp1[i] = dp2[i];
        }

    }

    // for(int i = 0;i < n;i++){
    //     cerr << pb1[i] << " ";
    // }
    // cerr << endl;

    // for(int i = 0;i < n;i++){
    //     cerr << dp1[i] << " ";
    // }
    // cerr << endl;

    //  for(int i = 0;i < n;i++){
    //     cerr << dp2[i] << " ";
    // }
    // cerr << endl;

    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans += dp1[i];
    }
    cout << ans << endl;
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