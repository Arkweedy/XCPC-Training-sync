#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 998244353;

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < min(n,32);i++){
        int l = *min_element(a.begin(),a.end()),r = *max_element(a.begin(),a.end());
        int m = l + r >> 1;
        for(int i = 0;i < n;i++){
            a[i] = abs(a[i] - m);
        }
    }
    if(n > 32){
        int x = count(a.begin(),a.end(),0), y = count(a.begin(),a.end(),1);
        ll ans = 1ll * x * y;
        ans %= P;
        cout<<ans<<endl;
    }
    else{
        ll ans = 0;
        for(int i = 0;i < n;i++){
            for(int j = i + 1;j < n;j++){
                ans += abs(a[i] - a[j]);
            }
        }
        ans %= P;
        cout<<ans<<endl;
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