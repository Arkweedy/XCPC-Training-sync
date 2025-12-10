#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, k;
    cin>>n>>k;
    vector<int>a(n);
    map<int,int>mp;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    ll ans = 0;
    for(int i = 0;i < n;i++){
        ans += mp[k - a[i]];
        if(k == a[i] * 2)ans--;
    }
    cout<<ans / 2<<endl;
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