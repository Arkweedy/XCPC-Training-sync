#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.15 21:37:39

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<int>dp(k + 1, 1);
    for(int i = 0;i <= k;i++){
        if(dp[i] == 0)continue;
        for(auto x : a){
            if(i + x > k)break;
            dp[i + x] = 0;
        }
    }

    if(dp[k] == 1){
        cout << "Second" << endl;
    }
    else{
        cout << "First" << endl;
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}