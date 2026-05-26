#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1699E2.cpp Create time : 2026.04.21 17:01

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>dp(m + 1);// min geq i, min max
    vector<int>ex(m + 1);
    vector<int>mc(m + 1);
    for(int i = 0;i < n;i++){
        ex[a[i]]++;
        if(ex[a[i]] == 1)mc[a[i]]++;
    }
    iota(dp.begin(), dp.end(), 0);
    int p = m;
    int ans = 1e9;
    int mi = *min_element(a.begin(),a.end());
    for(int i = m;i >= 1;i--){
        for(int j = i;1ll * i * j <= m;j++){
            if(dp[i * j] > max(dp[j], i)){
                if(ex[i * j]){
                    mc[dp[i * j]]--;
                    mc[max(dp[j], i)]++;
                }
                dp[i * j] = max(dp[j], i);
            }
        }
        while(mc[p] == 0)p--;
        if(i <= mi)ans = min(ans, p - i);
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