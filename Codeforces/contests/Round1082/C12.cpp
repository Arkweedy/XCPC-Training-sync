#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C12.cpp Create time : 2026.02.23 23:27

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    int ans = n;
    for(int i = n - 1;i >= 1;i--){
        if(a[i - 1] + 1 == a[i]){
            a.erase(a.begin() + i);
            ans--;
            if(i != a.size())i++;
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