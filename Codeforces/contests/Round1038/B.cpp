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
    vector<ll>a(n),b(n),c(n),d(n);
    for(int i = 0;i < n;i++){
        cin>>a[i]>>b[i]>>c[i]>>d[i];
    }
    ll sumz = 0, sumo = 0;
    for(int i = 0;i < n;i++){
        if(a[i] > c[i]){
            sumz += abs(a[i] - c[i]);
        }
        if(b[i] > d[i]){
            sumo += min(a[i], c[i]) + abs(b[i] - d[i]);
        }
    }
    ll ans = sumz + sumo;
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