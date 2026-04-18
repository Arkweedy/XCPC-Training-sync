#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.04.07 19:19:36

const int N = 2e5 + 10,mod = 998244353;

ll f[N],g[N],n,k,p[N],s[N];

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
    cin>>n>>k;
    s[0] = 1;
    for(int i=1;i<=n;i++){
        ll a,b;cin>>a>>b;
        p[i] = a * qmi(b,mod-2) % mod;
        s[i] = s[i-1] * p[i] % mod;
    }
    for(int i=k;i<=n;i++){
        if(i==k){
            f[i] = s[i];
        }else{
            f[i] = (s[i] * qmi(s[i-k],mod-2) % mod) * (1-p[i-k]+mod) % mod * (1 - g[i-k-1] + mod) % mod;
        }
        g[i] = (g[i-1] + f[i]) % mod;
    }

    cout<<g[n]<<'\n';
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