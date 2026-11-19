#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.11.08 00:04

void solve()
{
    int n, l;
    cin >> n >> l;
    l--;
    i64 sum = 0;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin(),a.end());
    int ma = a.back();

    vector<i64>pa(n - 1);
    for(int i = 0;i < n - 1;i++){
        pa[i] = a[i];
        if(i > 0)pa[i] += pa[i - 1];
    }
    
    // allow most 1 = k
    // others leq l / k
 
    auto calc = [&](int k)->i64
    {
        i64 res = 0;
        res += max(ma - k, 0);
        int t = min(l / k, k);
        int p = lower_bound(a.begin(),a.end(), t) - a.begin();
        res += pa[n - 2];
        if(p > 0)res -= pa[p - 1];
        res -= 1ll * t * (n - 2 - p + 1);
        return res;
    };

    i64 ans = calc(ma);
    for(int L = 1, R;L <= l; L = R + 1){
        R = l / (l / L);
        ans = min(ans, calc(R));
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