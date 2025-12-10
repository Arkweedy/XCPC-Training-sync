#include<bits/stdc++.h>
#define N 20
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using ll =long long ;
using ld =double ;
using namespace std;
const ld eps =1e-7;
int a[N];//a[i]为x^i的系数
int n,m,x,y;
int h[N],w[N];
ld ff(ld x)
{
    ld ans=0;
    for(int i=1;i<=m;i++)
    {
        ans+=a[i]*pow(x,i);
    }
    return ans;
}
ld f(ld x)
{
    ld ans=0;
    for(int i=1;i<=m;i++)
    {
        ans+=a[i]*(i)*pow(x,i-1);
    }
    ans=ans*ans;
    ans+=1;
    ans=sqrt(ans);
    return ans;
}
ld sinp(ld l,ld r){return (r-l)*(f(l)+f(r)+4*f((l+r)/2))/6;}
ld cal(ld l,ld r,ld v,int step)
{
	ld m=(l+r)/2;
	ld vl=sinp(l,m),vr=sinp(m,r);
	if(step<0&&abs(v-vl-vr)<15*eps) return vl+vr+(vl+vr-v)/15;
	return cal(l,m,vl,step-1)+cal(m,r,vr,step-1);
}
//cal(l,r,sinp(l,r),13)  使用方式
ld ans;
void output(long double x){
    static char s[25];
    sprintf(s,"%.4Le",x);
    for(int i:{0,1,2,3,4,5,6,7}) printf("%c",s[i]);
    printf("%c",s[strlen(s)-1]);
}
void solve()
{
    ans=1e18;
    cin>>n>>m>>x>>y;
    for(int i=1;i<=m;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>h[i]>>w[i];
    vector<int> p(n,0);
    for(int i=1;i<=n;i++) p[i-1]=i;
    mt19937_64 g(time(0));
    do{
        if(g() % 5 <= 1)continue;
        ld con=0;
        ld po=0;
        for(int i=0;i<n;i++)
        {
        //  cerr<<po<<endl;
            int hh=h[p[i]],ww=w[p[i]];
            con+=ww*cal(0,po,sinp(0,po),5);
            if(con>ans) break;
            if(i==n-1) break;
            ld xx=po,yy=hh+ff(po);
            ld yyy=ff(po);
            ld k=(yy-y)/(xx-x);
            ld b=y-k*x;
            ld l=po,r=po+1e3;
            for(int j=0;j<=30;j++)
            {
                ld m=(l+r)/2;
                ld my=ff(m);
                if(ff(m)<k*m+b) l=m;
                else if(max(hh,h[p[i+1]])>sqrt((yyy-my)*(yyy-my)+(xx-m)*(xx-m))) l=m;
                else r=m;
            }
            po=max(po,r);
        }
        ans=min(ans,con);
        //cerr<<con<<endl;
    }while(next_permutation(p.begin(),p.end()));
    output((long double)ans);
    putchar('\n');
}

int main()
{
    ios::sync_with_stdio(false);//cin.tie(0);
    int tt=1;
    cin>>tt;
    while(tt--)
    {
        solve();
    }
    return 0;
}