#include<bits/stdc++.h>

using namespace std;
#define int long long 

void solve()
{
    int n;
    cin >> n;
    vector <vector <int>> v(n + 1);
    
    vector <int> dp((1ll << n));
    string s;
    cin >> s;
    dp[0] = 1;
    
    for(int i=0;i<s.size();i++){
        if(s[i] == '0') v[std::__popcount(i + 1)].push_back(i + 1);
    }
    for(int i=1;i<=n;i++){
        for(auto x : v[i]){
            for(int j=0;j<n;j++){
                if((x >> j) & 1){
                    int now = x - (1ll << j);
                    // cout << x << " " << now << "\n";
                    dp[x] |= dp[now];
                }
            }
            
        }
    }
    // cout << (1ll << n) - 1 << "\n";
    if(dp[(1ll << n)-1]){
        cout << "Yes\n";
    }else cout << "No\n";


}

signed main()
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