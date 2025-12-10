#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    auto check = [&](int len)->bool
    {
        ll cnt = 0;
        for(auto x : a){
            cnt += x / len;
        }
        return cnt >= k;
    };

    int l = 0, r = 1145141919;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout<<l<<endl;
    return;
}

int main()
{
    freopen("stick.in","r",stdin);
    freopen("stick.out","w",stdout);

    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}