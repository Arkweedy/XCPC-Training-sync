#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,m;
    cin>>n>>m;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    map<ll,int>mp;
    mp[0] = 1;// attention
    ll sum = 0;
    ll ans = 0;
    for(int i = 0;i < n;i++){
        sum += a[i];
        ans += mp[sum - m];
        mp[sum]++;
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