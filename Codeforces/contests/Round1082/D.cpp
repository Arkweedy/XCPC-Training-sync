#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.23 23:44

void solve()
{
    int n, k;
    cin >> n >> k;
    if(k < n){
        cout << "No" << endl;
        return;
    }
    int t = n / 2;
    if(n * 2 - 1 < k){
        cout << "No" << endl;
        return;
    }
    auto ca = [&](int x)->int
    {
        return x;
    };

    auto cb = [&](int x)->int
    {
        return x * 2 - 1;
    };

    int l = 0, r = n + 1;
    while(r - l > 1){
        int m = l + r >> 1;
        if(ca(m) + cb(n - m) >= k){
            l = m;
        }
        else{
            r = m;
        }
    }
    // l ok
    vector<int>ans, ans2;
    for(int i = 0;i < l;i++){
        ans.push_back(i + 1);
        ans.push_back(i + 1);
    }
    for(int i = l;i < n - 1;i++){
        ans.push_back(i + 2);
        ans.push_back(i + 1);
    }
    if(l != n){
        ans.push_back(l + 1);
        ans.push_back(n);
    }
    
    cout << "Yes" << endl;
    for(int i = 0;i < n * 2;i++){
        cout << ans[i] << " ";
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