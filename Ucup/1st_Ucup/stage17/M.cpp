#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 21:45:33

const int mod = 998244353;

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}

void solve()
{
    int n;cin>>n;
    vector<ll>a(n),fact(n);

    fact[0] = 1;
    for(int i=1;i<=n;i++)fact[i] = fact[i-1] * i % mod;
    for(int i=0;i<n;i++)cin>>a[i];
    string s;cin>>s;

    ll res = 0;
    for(int i=0;i<n;i++){
        ll ans = 1;
        for(int j=0;j<i;j++){
            if(s[j] == '-')ans = ans * (1-2 * qmi(i-j,mod-2) % mod + mod) % mod;
        }
        res = (res + ans * a[i] % mod * fact[n-1]) % mod;
    }

    cout<<res<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}