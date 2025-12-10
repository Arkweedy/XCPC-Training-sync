#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int l,n;
    cin>>l>>n;
    vector<pair<int,int>>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin(),a.end());
    int r = 0;
    int ans = 0;
    for(int i = 0;i < n;i++){
        if(a[i].first > r){
            ans += a[i].first - r;
            r = a[i].second + 1;
        }
        else{
            r = max(r, a[i].second + 1);
        }
    }
    ans += l + 1 - r;
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