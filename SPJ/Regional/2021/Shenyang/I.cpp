#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 998244353;
constexpr long double eps=1e-7;
using ld =long double ;
struct com{ld x,y;};
com operator +(com a,com b){return com{a.x+b.x,a.y+b.y};}
com operator -(com a,com b){return com{a.x-b.x,a.y-b.y};}
com operator *(com a,com b){return com{a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
com inv(com a)
{
    ld d=a.x*a.x+a.y*a.y;
    //cout<<d<<endl;
    return com{a.x/d,-a.y/d};
}
com a[4][5];
void read(com &a)
{
    int x,y;cin>>x>>y;
    a={(ld)x,(ld)y};
}
void print(com a)
{
    //cout<<a.x;
    cout<<fixed<<setprecision(10)<<a.x<<' '<<a.y<<'\n';
    //cout<<fixed<<setprecision(2)<<a.x<<' '<<a.y<<' '<<' ';
}
void pr()
{
    for(int i=1;i<=3;i++)
    {
        for(int j=1;j<=4;j++) print(a[i][j]),cout<<' ';
        cout<<endl;
    }
    cout<<endl;
}
int  guess()
{
    //pr();
    for(int i=1;i<=3;i++)
    {
        int j,cnt=0;
        for(j=i;j<=3;j++)
            if(abs(a[j][i].x)>eps||abs(a[j][i].y)>eps) 
            {
                cnt=1;
                break;
            }
        if(!cnt) return 0;
        swap(a[i],a[j]);
        com in=inv(a[i][i]);
        for(int k=i;k<=4;k++) a[i][k]=a[i][k]*in;
        for(int j=1;j<=3;j++)
            if(j!=i)
            {
                com p=a[j][i];
                for(int k=i;k<=4;k++) a[j][k]=(a[j][k]-p*a[i][k]);
            }


        //pr();
    }
    return 1;
}
com zz[4],ww[4];
void solve()
{
    for(int i=1;i<=3;i++)
    {
        com z,w;
        read(z);read(w);
        zz[i]=z,ww[i]=w;
        a[i][1]=z;
        a[i][2]=com{1,0};
        a[i][3]=w*z*com{-1,0};
        a[i][4]=w;
    }
    int can=guess();
    if(can)
    {
        com aa=a[1][4],bb=a[2][4],cc=a[3][4];
//    print(aa);print(bb);print(cc);
        com z;read(z);
        com p=aa*z+bb,q=cc*z+com{1,0};
        p=p*inv(q);
        print(p);
    }
    else 
    {
        for(int i=1;i<=3;i++)
            for(int j=1;j<=4;j++ ) a[i][j]={0,0};
        for(int i=1;i<=3;i++) zz[i]=inv(zz[i]);
        for(int i=1;i<=2;i++)
        {
            a[i][1]={1,0};
            a[i][2]=zz[i];
            a[i][4]=ww[i];
        }
        int can=guess();
        com z;read(z);z=inv(z);
        com aa=a[1][4],bb=a[2][4];
        z=aa+bb*z;
        print(z);
    }
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
}