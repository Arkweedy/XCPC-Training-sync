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
    ll ans = a[0] + a[1];
    if(n >= 3 && a[0] < a[1]){
        ans = min(ans, a[0] * 2ll);
    }

    auto b = a;
    for(int i = 1;i < n;i++){
        b[i] = min(b[i], b[i - 1]);
    }
    ll res = 0;
    for(int i = 0;i < n;i++){
        res += b[i];
    }
    ans = min(ans,res);
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