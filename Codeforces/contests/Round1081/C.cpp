#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.21 23:01

void solve()
{
    int n, h, k;
    cin >> n >> h >> k;
    vector<int>a(n);
    i64 sum = 0;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        sum += a[i];
    }
    vector<int>mi(n),ma(n + 1);
    vector<i64>ps(n);
    for(int i = 0;i < n;i++){
        mi[i] = a[i];
        ps[i] = a[i];
        if(i > 0){
            mi[i] = min(mi[i],mi[i - 1]);
            ps[i] += ps[i - 1];
        }
    }
    for(int i = n - 1;i >= 0;i--){
        ma[i] = a[i];
        if(i < n - 1)ma[i] = max(ma[i],ma[i + 1]);
    }
    vector<int>v(n);
    for(int i = 0;i < n;i++){
        v[i] = max(ma[i + 1] - mi[i], 0);
    }

    int t = (h - 1) / sum;
    i64 ans = 1ll * t * (n + k);
    h -= t * sum;
    for(int i = 0;i < n;i++){
        if(ps[i] + v[i] >= h){
            ans += i + 1;
            break;
        }
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