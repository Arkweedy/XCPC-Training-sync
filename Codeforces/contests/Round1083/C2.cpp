#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C2.cpp Create time : 2026.02.26 23:21



void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>a(n);
    int sum = 0;
    for(int i = 0;i < n;i++){
        int k;
        cin >> k;
        sum += k;
        a[i].resize(k);
        for(int j = 0;j < k;j++){
            cin >> a[i][j];
        }
        reverse(a[i].begin(),a[i].end());
        vector<int>na;
        set<int>s;
        for(int j = 0;j < k;j++){
            if(!s.count(a[i][j]))na.push_back(a[i][j]);
            s.insert(a[i][j]);
        }
        a[i] = move(na);
    }
    vector<int>ans;
    for(int j = 0;j < n;j++){
        sort(a.begin(),a.end());
        int p = 0;
        while(p < n && a[p].empty())p++;
        if(p == n)break;
        set<int>ers;
        for(int j = 0;j < a[p].size();j++){
            ans.push_back(a[p][j]);
            ers.insert(a[p][j]);
        }
        vector<vector<int>>na(n);
        for(int j = 0;j < n;j++){
            for(int k = 0;k < a[j].size();k++){
                if(!ers.count(a[j][k]))na[j].push_back(a[j][k]);
            }
        }
        a = move(na);
    }
    for(auto x : ans){
        cout << x << " ";
    }
    cout << "\n";
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