#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,x,y,z;
    cin>>n>>x>>y>>z;
    vector<int>a(n);
    for(int i = 0; i< n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    ll ans = x;
    ll eq = 0;
    for(int i = 0;i < n - 1;i++){
        if(a[i + 1] > a[i]){
            ans += x;
        }
        else if(a[i + 1] == a[i]){
            ans += y;
            eq++;
        }
    }
    if(x + z > y * 2){
        ll cnt = eq / 2;
        ans -= cnt * y * 2;
        ans += cnt * (x + z) * 2;
    }
    cout<<ans<<endl;
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