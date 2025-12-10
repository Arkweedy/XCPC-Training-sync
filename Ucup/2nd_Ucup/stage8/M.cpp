#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 300009;
int n,a[N],b[N],c[N],d[N],s[N],ma[N];
int check(int p){
    for(int i=1;i<=n;i++) c[i]=(a[i]>=p),d[i]=(b[i]>=p);
    int sum=0,ans;
    for(int i=1;i<=n;i++)
    {
        sum+=c[i];
        s[i]=s[i-1]+d[i]-c[i];
    }
    for(int i=n;i;i--)
    {
        if(i==n) ma[i]=s[i];
        else ma[i]=max(ma[i+1],s[i]);
    }
    ans=sum;
    for(int i=0;i<n;i++)
    {
        ans=max(ans,sum+ma[i+1]-s[i]);
    }
    return ans>=(n+1)/2;
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    int l=0,r=1e9+1;
    while(r-l>1)
    {
        int m=l+r>>1;
        if(check(m)) l=m;
        else r=m;
    }
    cout<<l;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
   // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
