#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 15:45:59

void solve()
{
    int n;
    cin >> n;
    int m = 0;
    vector<vector<int>>a(n);
    vector<int>e;
    for(int i = 0;i < n;i++){
        int k;
        cin >> k;
        m += k;
        a[i].resize(k);
        for(int j = 0;j < k;j++){
            cin >> a[i][j];
            e.push_back(a[i][j]);
        }
        sort(a.begin(),a.end());
    }
    sort(e.begin().e.end());
    for(int i = 0;i < n;i++){
        for(auto&x : a[i]){
            x = lower_bound(e.begin(),e.end(), x);
        }
    }
    sort(a.begin(),a.end());

    vector<int>dp(m);
    for(int i = 0;i < n;i++){
        vector<int>ndp(m);
        
    }


    
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