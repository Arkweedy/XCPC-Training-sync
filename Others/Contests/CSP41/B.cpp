#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.04.02 20:49



void solve()
{
    //
    int n = 10;
    vector<int>x, y;
    // \frac{x}{y}
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j)->bool
    {
        return 1ll * x[i] * y[j] > 1ll * x[j] * y[i];
    });
    
    int id = lower_bound(x.begin(), x.end(), 10) - x.begin();

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