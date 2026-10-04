#include<bits/stdc++.h>

using ll = long long;
using namespace std;

void solve()
{
    int n;
    cin>>n;
    ll x, y;
    cin>>x>>y;
    vector<int>a(n);
    map<int,int>mp;
    int macnt = 0;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        mp[a[i]]++;
        macnt = max(macnt, mp[a[i]]);
    }
    sort(a.begin(),a.end());
    ll ans = (n - macnt) * y;

    for(int i = 0;i < n;i++){
        ans = min(ans, a[i] * x + (n - i - 1) * y);
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
