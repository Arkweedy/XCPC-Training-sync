#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 2e5 + 10;
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
int getc(int a,int b)
{
    if(a<b||a<0||b<0) return 0;
    return 1ll*p[a]*ip[b]%mod*ip[a-b]%mod;
}
void solve()
{
    int n,m;
    cin>>n>>m;
    cout<<1ll*p[n]*getc(n-1,m-1)%mod<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    pre();
    while(tt--){
        solve();
    }
    return 0;
}