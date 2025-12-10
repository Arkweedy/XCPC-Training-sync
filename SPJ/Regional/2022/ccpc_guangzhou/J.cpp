#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 1.5e7 + 10;
constexpr int P = 998244353;

constexpr int mod=998244353;
int p[N],ip[N];
void pre()
{
    p[0]=1;
    for(int i=1;i<N;i++) p[i]=1ll*i*p[i-1]%mod;
    ip[0]=ip[1]=1;
    for(int i=2;i<N;i++) ip[i]=1ll*(mod-mod/i)*ip[mod%i]%mod;
    for(int i=2;i<N;i++) ip[i]=1ll*ip[i]*ip[i-1]%mod;
}
int binom(int a,int b)
{
    if(a<b||a<0||b<0) return 0;
    return 1ll*p[a]*ip[b]%mod*ip[a-b]%mod;
}

void solve()
{
    int n, m;
    cin>>n>>m;
    m = (m + 1) / 2;
    //[1,m] ok
    auto reflex = [&](int a, int x)->int //point a reflex by point x
    {
        return 2 * x - a;
    };

    auto path = [&](int y)->int
    {
        int res = 0;
        for(int i = abs(n - y) % 2;i <= m;i += 2){
            int free = (n - abs(y - i)) / 2;
            res += binom(n, free);
            res %= P;
        }
        return res;
    };

    auto calc = [&]()->ll
    {
        ll res = -path(0);
        int k = (n + m - 1) / m;
        int l = 0, r = 0;
        int sign = 1;
        for(int i = 0;i <= k;i++){
            res = (res + path(l) * sign + P) % P;
            res = (res + path(r) * sign + P) % P;
            l = reflex(l,m + 1);
            r = reflex(r,-1);
            swap(l, r);
            sign *= -1;
        }
        return res;
    };

    ll ans = calc();
    ans = (ans + P) % P;
    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}