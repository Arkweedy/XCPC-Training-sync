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
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin(),a.end(),[&](pair<int,int>i,pair<int,int>j)->bool
    {
        return i.first == j.first ? i.second > j.second : i.first < j.first;
    });
    int r = -1;
    int ans = n;
    for(int i = 0;i < n;i++){
        if(a[i].second <= r){
            ans--;
        }
        else{
            //cerr<<a[i].first<<" "<<a[i].second<<endl;
            r = max(r,a[i].second);
        }
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