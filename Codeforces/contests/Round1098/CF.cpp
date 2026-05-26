#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//CF.cpp Create time : 2026.05.17 00:41

void solve()
{
    i64 a, n;
    cin >> a >> n;
    vector<int>c(10);
    int ma = 0, mi = 9;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x] = 1;
        ma = max(ma, x);
        mi = min(mi, x);
    }

    auto check = [&](i64 x)->bool
    {
        while(x){
            if(!c[x % 10])return false;
            x /= 10;
        }
        return true;
    };

    constexpr i64 inf = 2e18;
    i64 ans = inf;
    if(c[0])ans = a;
    for(int i = 1;i <= a;i++){
        if(check(i)){
            ans = a - i;
        }
    }
    for(int i = 0;i < ans;i++){
        if(check(i + ans)){
            ans = i;
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