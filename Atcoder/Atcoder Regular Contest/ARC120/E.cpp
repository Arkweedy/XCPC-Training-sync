#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.12 19:25

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    

    auto check = [&](int k)->bool
    {
        vector<int>dp0(n), dp1(n);
        //dp0 -> at least left t
        //dp1 -> at most right t
        dp0[0] = 0, dp1[0] = k;
        for(int i = 1;i < n;i++){
            int t = (a[i] - a[i - 1] + 1) / 2;
            int d = a[i] - a[i - 1];
            dp0[i] = dp0[i - 1] + t;
            if(dp1[i - 1] >= t)dp0[i] = min(dp0[i], t);
            dp1[i] = (2 * k - 2 * dp0[i - 1] - d) / 2;
            dp1[i] = max(dp1[i], (2 * dp1[i - 1] - d) / 2);
        }

        if(dp0[n - 1] <= k){
            return true;
        }
        else{
            return false;
        }
    };

    int l = 0, r = 1e9;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){
            r = m;
        }
        else{
            l = m;
        }
    }
    cout << r << endl;
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