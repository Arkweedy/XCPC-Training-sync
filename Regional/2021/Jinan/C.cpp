#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e6 + 10;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
constexpr int mod=998244353;
int p[N],ip[N];
int n,tot[N];
int b[N],cnt;
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
    if(a<0||b<0||a<b) return 0;
    return 1ll*p[a]*ip[b]%mod*ip[a-b]%mod;
}
void solve()
{
    pre();
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int a;cin>>a;tot[a]++;
    }
    for(int i=1;i<N;i++)
        if(tot[i]) b[++cnt]=tot[i];
    //for(int i=1;i<=cnt;i++) cout<<b[i]<<endl;
    int ans=1;
    for(int i=1;i<=cnt;i++) ans=1ll*ans*p[b[i]]%mod;
    int s=0;
    for(int i=1;i<=cnt;i++)
    {
        ans=1ll*ans*getc(s+b[i]/2,s)%mod;
        s+=b[i];
    }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t = 1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}