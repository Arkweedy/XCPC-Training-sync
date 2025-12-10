#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.02 14:24:20

void solve()
{
    int n, k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end(),[&](int i, int j)->bool
    {
        return i % k > j % k;  
    });
    int m;
    cin>>m;
    ll ans = 0;
    for(int i = 0;i < n;i++){
        if(k - a[i] % k <= m){
            m -= k - a[i] % k;
            ans++;
        }
        ans += a[i] / k;
    }
    ans += m / k;
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