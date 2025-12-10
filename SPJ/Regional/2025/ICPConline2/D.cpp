#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1e5 + 10;
constexpr int P = 998244353;
constexpr int mod = 998244353;
//void check()
//{
//    constexpr int n = 6;
//    int len = 1 << n;
//    vector<int>cnt(n)
//    for(int i = 0;i < len;i++){
//        vector<int>vec;
//        for(int j = 0;j < n;j++){
//            if(i >> j & 1){
//                vec.push_back(j);
//            }
//        }
//
//    }
//}

ll power(ll a, ll p)
{
    ll res = 1;
    while(p){
        if(p & 1)res = res * a % P;
        a = a * a % P;
        p >>= 1;
    }
    return res;
}

ll inv(int a)
{
    return power(a, P - 2);
}

void solve()
{
    int n;
    cin>>n;
    vector<int>a(1+n);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    sort(a.begin()+1,a.end(),greater<int>());
    ll p = 1;
    ll ans = 0;
    ll inv2 = inv(2);
    for(int i = 1;i <= n;i++){
        ans=(ans+1ll*a[i]*power(2,i-1)%mod*(1+1ll*(power(3,n-i)-1)*inv2 % mod )%mod)%mod;
    }
    ans=(ans+mod)%mod;
    cout<<ans<<endl;
    return;
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
