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
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<ll>ans = a;
    for(int i = 1;i < n;i++){
        ans[i] += ans[i - 1];
    }
    for(int i = 1;i < n;i++){
        ans[i] += ans[i - 1];
    }

    ll ma = -1;
    for(int i = 0;i < n;i++){
        ma = max(ma, a[i]);
        ans[i] += ma * (i + 1);
    }

    for(int i = 0;i < n;i++){
        cout<<ans[i]<<"\n";
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