#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<pair<int,int>>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i].first;
    }
    for(int i = 0;i < n;i++){
        cin>>a[i].second;
    }
    sort(a.begin(),a.end(),[&](const pair<int,int>&i, const pair<int,int>&j)->bool
    {
        return i.second - i.first < j.second - j.first;
    });
    int need = n / 2 + 1;
    ll ans = 0;
    for(int i = 0;i < need;i++){
        ans += max(a[i].second - a[i].first, 0);
    }
    cout<<ans<<endl;
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