#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 1e9 + 7;
#define double long double 
double  vx,vvy;
double y,yy,vy1,vy2;
double x,xx,vx1,vx2;
double ax,ay;
void solve()
{
//return ;
    cin>>ax>>ay>>vx>>vvy;
    cin>>y>>yy>>vy1>>vy2;
    cin>>x>>xx>>vx1>>vx2;
    vx1*=-1;
    double T=(yy-y)*1.0/(vy1+vy2);
    double ay=y+T*vy1;
    if(vx1==0&&vx2==0)
    {
        double s=vx*T+(ax-x);
        s=fmod(s,2*(xx-x));
        if(s<0) s+=2*(xx-x);
        if(s<=(xx-x)) ax=x+s;
        else ax=xx-(s-(xx-x));
    }
    else 
    {
        //cout<<T<<endl;
        while(T>1e-6)
    {
        if(vx>0)
        {
            //cout<<1;
            double t=1e9;
            if(vx2<vx) t=1.0*(xx-ax)/(vx-vx2);
            double tt=min(t,T);
            ax+=tt*vx;
            x+=vx1*tt;
            xx+=vx2*tt;
            vx*=-1;
            T-=tt;
        }
        else 
        {
            double t=1e9;
            if(vx1>vx) t=1.0*(ax-x)/(vx1-vx);
            double tt=min(t,T);
            ax+=tt*vx;
            x+=vx1*tt;
            xx+=vx2*tt;
            vx*=-1;
            T-=tt;
        }
    }
    }
    cout<<fixed<<setprecision(10)<<ax<<' '<<ay<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}