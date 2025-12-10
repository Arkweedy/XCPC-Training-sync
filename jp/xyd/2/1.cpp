#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    ll ans = LLONG_MIN;
    ll sum = 0;
    for(int i = 0;i < m;i++){
        sum += a[i];
    }
    ans = max(ans,sum);
    for(int i = m;i < n;i++){
        sum -= a[i - m];
        sum += a[i];
        ans = max(ans, sum);
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