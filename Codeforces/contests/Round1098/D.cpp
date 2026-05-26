#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.05.17 00:08



void solve()
{
    int n;
    cin >> n;
    vector<pair<int,int>>a(n);
    vector<int>x,y;
    for(int i = 0;i < n;i++){
        cin >> a[i].first >> a[i].second;
        x.push_back(a[i].first);
        y.push_back(a[i].second);
    }
    sort(x.begin(),x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    sort(y.begin(),y.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    for(auto& [u, v] : a){
        u = lower_bound(x.begin(),x.end(), u) - x.begin();
        v = lower_bound(y.begin(),y.end(), v) - y.begin();
    }

    sort(a.begin(),a.end());
    int m1 = x.size(), m2 = y.size();
    vector<int>lu(m1),ld(m1),ru(m1),rd(m1);

    int mi = m2, ma = -1;
    int p = 0;
    for(int i = 0;i < m1;i++){
        while(p < n && a[p].first == i){
            mi = min(mi, a[p].second);
            ma = max(ma, a[p].second);
            p++;
        }
        lu[i] = ma;
        ld[i] = mi;
    }
    mi = m2, ma = -1;
    p = n - 1;
    for(int i = m1 - 1;i >= 0;i--){
        while(p >= 0 && a[p].first == i){
            mi = min(mi, a[p].second);
            ma = max(ma, a[p].second);
            p--;
        }
        ru[i] = ma;
        rd[i] = mi;
    }

    i64 ans = 1ll * (m1 - 1) * (m2 - 1);

    for(int i = 0; i < m1 - 1;i++){
        ans -= (m2 - 1) - max(min(lu[i], ru[i + 1]) - max(ld[i], rd[i + 1]), 0);
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