#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.03.14 22:33

void solve()
{
    int n;
    cin >> n;
    vector<int>c(n * n + 1);
    for(int i = 0;i < n * n ;i++){
        int e;
        cin >> e;
        c[e]++;
    }
    int lim = (n - 1) * n;
    for(int i = 0;i <= n * n;i++){
        if(c[i] > lim){
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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