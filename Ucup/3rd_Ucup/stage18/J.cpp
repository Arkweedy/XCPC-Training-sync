#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 11:21:15

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    map<int,vector<int>>mp;
    for(int i = 0;i < n;i++){
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    auto ck = [&](int p, int val)->bool
    {
        array<int,3>arr = {a[p], a[(p - 1 + n) % n], a[(p + 1) % n]};
        sort(arr.begin(),arr.end());
        return val == arr[0] || val == arr[2];
    };

    auto ckm = [&](int p)->bool
    {
        return ck(p, a[p]) || ck((p - 1 + n) % n, a[p]) || ck((p + 1) % n, a[p]);
    };



    vector<int>ans(n);

    for(auto [x, v] : mp){
        int ok = 0;
        for(auto p : v){
            ok |= ckm(p);
        }
        int res = n - v.size();
        if(!ok)res++;
        for(auto p : v){
            ans[p] = res;
        }
    }

    for(int i = 0;i < n;i++){
        cout << ans[i] << " ";
    }
    cout << endl;

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