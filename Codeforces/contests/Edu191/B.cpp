#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//B.cpp Create time : 2026.06.09 22:44

void solve()
{
    int n;
    cin >> n;
    vector<int>ans;
    ans.reserve(n * 4);
    if(n % 2 == 0){
        for(int i = 1;i <= n;i += 2){
            ans.push_back(i);
            ans.push_back(i + 1);
            ans.push_back(i);
            ans.push_back(i);
            ans.push_back(i + 1);
            ans.push_back(i + 1);
            ans.push_back(i);
            ans.push_back(i + 1);
        }
    }
    else{
        for(int i = 1;i <= n - 3;i += 2){
            ans.push_back(i);
            ans.push_back(i + 1);
            ans.push_back(i);
            ans.push_back(i);
            ans.push_back(i + 1);
            ans.push_back(i + 1);
            ans.push_back(i);
            ans.push_back(i + 1);
        }
        //1 1 2 1 2 3 1 3 2 2 3 3
        ans.push_back(n - 1);
        ans.push_back(n - 1);
        ans.push_back(n - 2);
        ans.push_back(n - 1);
        ans.push_back(n - 2);
        ans.push_back(n - 0);
        ans.push_back(n - 1);
        ans.push_back(n - 0);
        ans.push_back(n - 2);
        ans.push_back(n - 2);
        ans.push_back(n - 0);
        ans.push_back(n - 0);
    }

    for(auto x : ans){
        cout << x << " ";
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