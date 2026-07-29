#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.07.16 22:51

void solve()
{
    int n, c;
    cin >> n >> c;
    vector<int>a(n);
    int cnt = 0; // geq c
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(a[i] >= c){
            cnt++;
        }
    }
    sort(a.begin(),a.end());
    if(cnt * 2 < n){
        i64 ans = 0;
        int ha = n / 2;
        for(int i = ha;i < n;i++){
            ans += a[i] - c;
        }
        cout << ans << endl;
    }
    else{
        int les = n - cnt;
        i64 ans = 0;
        for(int i = les;i < n;i++){
            ans += a[i] - c;
        }
        cout << ans << endl;
    }
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