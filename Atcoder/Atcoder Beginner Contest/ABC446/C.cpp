#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.21 20:07

void solve()
{
    int n, d;
    cin >> n >> d;
    vector<int>a(n), b(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
    }
    int p = 0;
    for(int i = 0;i < n;i++){
        //day i
        
        //
        while(a[p] <= b[i]){
            b[i] -= a[p];
            p++;
        }
        a[p] -= b[i];
        //
        while(p + d <= i)p++;
    }
    int ans = 0;
    for(int i = p;i < n;i++){
        ans += a[i];
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