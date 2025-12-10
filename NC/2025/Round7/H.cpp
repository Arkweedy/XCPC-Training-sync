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
    vector<int>a(n + 1);
    vector<ll>id(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
        id[a[i]] = i;
    }
    ll ans = - n * (n + 1) / 2;
    ll l = n + 1,r = 0;
    cerr<<"calc:"<<endl;
    for(int i = 1;i <= n;i++){
        //not include any number
        ans += l * (l - 1) / 2 + (n - r) * (n - r + 1) / 2;
        cerr<<" += "<<l * (l - 1) / 2 + (n - r) * (n - r + 1) / 2<<endl;
        l = min(l,id[i]);
        r = max(r,id[i]);
        cerr<<l<<" "<<r<<endl;
        //i's attribute
        ans += l * (n - r + 1);
        cerr<<" += "<<l * (n - r + 1)<<endl;
        
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