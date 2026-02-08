#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.07 20:09

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    int ma = a.back();
    int p = n - 1;
    while(p >= 0 && a[p] == ma)p--;
    vector<int>ans;
    if(p % 2 == 1){
        int ok = 1;
        for(int i = 0;i * 2 < p;i++){
            if(a[i] + a[p - i] != ma){
                ok = 0;
                break;
            }
        }
        if(ok)ans.push_back(ma);
    }
    if(p == -1)ans.push_back(ma);
    if(n % 2 == 0){
        int ok = 1;
        for(int i = 0;i * 2 < n;i++){
            if(a[i] + a[n - i - 1] != ma + a[0]){
                ok = 0;
                break;
            }
        }
        if(ok)ans.push_back(ma + a[0]);
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
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}