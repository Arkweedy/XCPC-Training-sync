#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.05.16 22:33

void solve()
{
    int n;
    cin >> n;
    vector<int>a(3);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        a[x]++;
    }
    int ans = a[0] + min(a[1], a[2]) + (max(a[1], a[2]) - min(a[1], a[2])) / 3;
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