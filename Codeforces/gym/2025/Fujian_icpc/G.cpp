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
    for(int i = n - 1;i > 0;i--){
        a[i] -= a[i-1];
        a[i] = max(a[i],0ll);
    }
    for(int i = 1;i < n;i++){
        a[i] += a[i-1];
    }
    ll k;
    cin>>k;
    while(m--){
        int l, r;
        cin>>l>>r;
        cout<<k + a[r-1]-a[l-1]<<endl;
    }
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