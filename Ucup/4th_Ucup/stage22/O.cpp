#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
constexpr ll mod=998244353;
using namespace std;
ll qp(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;b>>=1;
    }
    return ans;
}
void solve()
{ 
    ll n;
    cin>>n;
    ll ans=(qp(4,n)-3*qp(3,n)-1+3*qp(2,n))%mod;
    ans=(ans%mod+mod)%mod;
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}