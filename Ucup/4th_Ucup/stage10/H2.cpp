#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//H2.cpp Create time : 2026.01.02 23:55

void solve()
{
    int n;
    cin >> n;
    map<int,int>mp;
    int ma = -1;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        mp[x]++;
        ma = max(ma, x);
    }
    
    int oc = 0;
    for(auto [x, c] : mp){
        oc = max(oc, c);
    }

    vector<vector<int>>ans(oc);
    for(auto [x, c] : mp){
        if(x != ma){
            for(int i = 0;i < c;i++){
                ans[i].push_back(x);
            }
        }
        else{
            for(int i = 0;i < c;i++){
                ans[oc - i - 1].push_back(x);
            }
        }
    }

    int res = 0;
    int pre = 0;
    for(int i = 0;i < oc;i++){
        for(auto x : ans[i]){
            res += pre / x;
            pre = x;
        }
    }
    
    cout << res << endl;
    for(auto v : ans){
        for(auto x : v){
            cout << x << " ";
        }
    }
    cout << endl;
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