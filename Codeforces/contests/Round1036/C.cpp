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
    vector<ll>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    a[0] = 1;
    ll x = 1;
    for(int i = 1;i <= n - 1;i++){
        if(a[i + 1] % a[i] != 0){
            x = lcm(x, lcm(a[i],a[i + 1]) / a[i + 1]);
        }
    }
    cout<<x<<endl;
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