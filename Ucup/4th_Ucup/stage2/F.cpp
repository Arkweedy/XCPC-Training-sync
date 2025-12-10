#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e6 + 10;
constexpr int mod=998244353;
int n,k;
int r[N],c[N];
int b[N],len;
int a[2][N];
int find(int p){return lower_bound(b+1,b+len+1,p)-b;}
int qp(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;b>>=1;
    }
    return ans;
}
void solve()
{
    cin>>n>>k;
    int cnt=0;
    for(int i=1;i<=k;i++) cin>>r[i]>>c[i],b[++cnt]=c[i];

    sort(b+1,b+cnt+1);
    len =unique(b+1,b+cnt+1)-b-1;
    for(int i=0;i<2;i++)
        for(int j=1;j<=len;j++) a[i][j]=0;
    for(int i=1;i<=k;i++) a[r[i]-1][find(c[i])]++;


    int ma[2]={0,0},mi[2]={len+1,len+1};
    for(int i=0;i<2;i++)
        for(int j=1;j<=len;j++)
            if(a[i][j]) ma[i]=max(ma[i],j),mi[i]=min(mi[i],j);

    if(ma[0]==0||ma[1]==0)
    {
        cout<<qp(2,2*k+2)<<'\n';
        return ;
    }

    int ans=0;
    for(int mask=0;mask<16;mask++)
    {
        int con=qp(2,k);
        int l[2]={1,1},r[2]={len,len};
        for(int i=0;i<4;i++)
            if(mask>>i&1)
            {
                if(i==0) l[0]=mi[0]+1;
                else if(i==1) r[0]=ma[0]-1;
                else if(i==2) l[1]=mi[1]+1;
                else r[1]=ma[1]-1;
            }
        //cout<<con<<endl;
        for(int i=1;i<=len;i++)
        {
            if(a[0][i]==1&&a[1][i]==1) continue;
            else if(a[0][i]==1)
            {
                if(i<=r[1]&&i>=l[1]) con=con*2%mod;
            }
            else if(a[1][i]==1)
            {
                if(i<=r[0]&&i>=l[0]) con=con*2%mod;
            }
        }
        //cout<<con<<endl;
        ans=(ans+con)%mod;
    }
    //cout<<endl;
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}