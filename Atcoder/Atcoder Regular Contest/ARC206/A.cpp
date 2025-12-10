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
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    ll ans = 1;
    map<int,int>mp;
    for(int i = 0;i < n;i++){
        ans -= mp[a[i]];
        if(i + 1 < n && a[i] != a[i + 1]){
            ans += n - i - 1;
            mp[a[i]]++;
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