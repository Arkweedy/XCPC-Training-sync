#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.02.23 22:58

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans += 1ll * (i + 1) * (n - i);
    }
    map<int,int>mp;
    vector<int>pre(n, -1);
    for(int i = 0;i < n;i++){
        if(mp.count(a[i] - 1))pre[i] = mp[a[i] - 1];
        else mp.clear();
        mp[a[i]] = i;
        for(auto it = mp.lower_bound(a[i] + 1);it != mp.end(); ){
            auto tmp = it;
            it++;
            mp.erase(tmp);
        }
    }

    for(int i = 1;i < n;i++){
        if(pre[i] != -1){
            ans -= 1ll * (pre[i] + 1) * (n - i);
        }
    }
    cout << ans << endl;
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