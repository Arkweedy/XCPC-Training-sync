#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1e5 + 10;
constexpr int mod=998244353;
int f[N];
int n,m,x,y;
int inv[N];
int query(int s,int t,int c)
{
    cout<<"?"<<' ';
    cout<<s<<' '<<t<<' '<<c<<' '<<endl;
    int ans;cin>>ans;
    return ans;
}
int cal(int p)
{
    if(p<n) return f[p];
    int ans=0;
    for(int i=0;i<n;i++)
    {
        int con=1;
        for(int j=0;j<n;j++)
        {
            if(j==i) continue;
            con=1ll*con*(p-j)%mod*inv[abs(i-j)]%mod;
            if(i<j) con=(mod-con)%mod;
        }
        con=1ll*con*f[i]%mod;
        ans=(ans+con)%mod;
    }
    ans=(ans+mod)%mod;
    return ans;
}
void solve()
{
    inv[0]=inv[1]=1;
    for(int i=2;i<N;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>x>>y;
    f[0]=0;
    for(int i=1;i<n;i++) f[i]=query(1,n,i);
    cout<<"!"<<endl;
    int k;cin>>k;
    cout<<cal(k);
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
   // cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
