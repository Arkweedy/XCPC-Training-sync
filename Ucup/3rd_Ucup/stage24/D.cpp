#include<bits/stdc++.h>
#define N 50050
using ll =long long ;
using namespace std;
int a[N],p[N],cnt,st;
int b[6000][6000];
//exgcd
#define ll long long 
ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b){x=1,y=0;return a;}
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
// a*x==b(mod c)
void  ff(ll a,ll b,ll c,ll &x,ll &y)
{
    ll d=exgcd(a,c,x,y);
    if(b%d){x=-1;return ;}
    y=c/d;
    x=(x%y*b/d%y+y)%y;
}

void pre()
{
    for(int i=2;i<N;i++)
    {
        if(!a[i]) p[++cnt]=i;
        for(int j=1;1ll*p[j]*i<N;j++) 
        {
            a[p[j]*i]=1;
            if(!(i%p[j])) break;
        }
    }
    //for(int i=1;i<5;i++) cerr<<p[i]<<endl;
    while(p[st]<=230) st++;
    for(int i=1;;i++)
    {
        //cerr<<i<<endl;
        int j=st+i-1;
        //cerr<<p[j]<<endl;
        if(j>cnt) break;
        ll A=1;
        b[i][0]=p[j];
        if(i==1)
        {
            b[i][1]=1;
            continue;
        }
        for(int jj=1;jj<i;jj++) A=1ll*A*b[jj][0]%p[j],b[i][jj]=b[i-1][jj];
        ll x,y;
        ff(A,1,p[j],x,y);
        b[i][i]=x;
        x=(x*A-1)/p[j];
        for(int jj=1;jj<i;jj++) b[i][jj]=-1ll*b[i][jj]*x%b[jj][0];
    }
}
int qp(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans*=a;
        a*=a;b>>=1;
    }
    return ans;
}
int aa[N],k[N],cntt;
void add(int pp)
{
    ll A=1;
    for(int i=pp+1;i<=cntt;i++) A=A*qp(p[i],k[i]);
    ll x,y;
    ll g=qp(p[pp],k[pp]);
    ff(A,1,g,x,y);
    aa[pp]=x;
    x=(x*A-1)/g;
    //cerr<<aa[1]<<aa[2];
    //cerr<<x;
    for(int jj=pp+1;jj<=cntt;jj++) aa[jj]=(-1ll)*aa[jj]*x%p[jj];
    //cerr<<aa[1]<<aa[2];
}
int cal(long double p)
{
    int g=(int) p;
    int a[3]={p-1,p,p+1};
    int ma=-1;
    long double maa=10;
    for(int i=0;i<3;i++)
    {
        if(abs(a[i]-p)<maa){
            maa=abs(a[i]-p);
            ma=i;
        }
    }
    return a[ma];
}
void solve()
{
    int n;cin>>n;
    if(n==1)
    {
        cout<<"1/1\n";return ;
    }
    else if(n==2)
    {
        cout<<"1/2\n";return ;
    }
    for(int i=1;i<=n;i++) aa[i]=0;
    cntt=0;
    for(cntt=1;p[cntt]<=n;cntt++)
    {
        ll g=p[cntt];k[cntt]=1;
        while(g<=n)
        {
            g*=p[cntt];
            k[cntt]++;
        }
        k[cntt]--;
    }
    cntt--;
    if(cntt>=st)
    {
        for(int i=st;i<=cntt;i++) aa[i]=b[cntt-st+1][i-st+1];
        for(int j=st-1;j;j--) add(j);
    }
    else
    {
        aa[cntt]=1;
        for(int j=cntt-1;j;j--) add(j);
    }
    long double  sum=0;
    for(int i=1;i<=cntt;i++)
    {
        int g=pow(p[i],k[i]);
        sum+=1.0L*aa[i]/g;
    }
    sum=-sum;
    sum=cal(sum);
    if(sum) cout<<sum<<'/'<<1;
    int cnt=0;
    if(!sum) cnt=1;
    for(int i=1;i<=cntt;i++)
    {
        int g=pow(p[i],k[i]);
        if(!aa[i]) continue;
        if(aa[i]>0) 
        {
            if(cnt) cnt--;
            else cout<<'+';
        }
        cout<<aa[i]<<"/"<<g;
    }
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    pre();
    int tt=1;
    cin>>tt;
    while(tt--)
    {
        solve();
    }
    return 0;
}