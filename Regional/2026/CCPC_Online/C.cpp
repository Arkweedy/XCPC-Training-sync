#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;
ll w,x,xx,y,u,v;
long double deal(ll w,ll x,ll xx,ll y,ll u,ll v){
    long double t=1e9;
    if(u==0){
        if(xx<=0||x>=0){
            t=0;
        }
        else {
            t=min(abs(xx),abs(x));
        }
        return sqrtl(y*y+t*t)/v;

    }
    else if(u<0){
        //cheqian
        if(x>=0&&-u*y<=x*v) t=0;

        //chehou
        if(xx<=0){
            t=0;
        }
        else {
            long double l=0,r=xx;
        for(int i=0;i<100;i++){
            long double m=(l+r)/2;
            long double tt=sqrtl(y*y+m*m)/v;
            if(xx+u*tt<=m) r=m;
            else l=m;
        }
        t=min(t,l);
        }
        return sqrtl(y*y+t*t)/v;
    }
    else {
        long double ans=1e9;
        //chehou
        if(x>=0) ans=1.0*y/v;
        else ans=min(ans,max(1.0L*y/v,1.0L*-x/u));

        //cheqian
        ll a=u*u-v*v,b=2*xx*v*v,c=u*u*y*y-v*v*xx*xx;
            __int128 dd=(__int128)b*b-(__int128)4*a*c;
            long double ddd=dd;ddd=sqrtl(ddd);

            long double a1,a2;
            if(dd>=0){
                a1=(-b-ddd)/(2*a);
                a2=(-b+ddd)/(2*a);
            }
        if(a1>a2) swap(a1,a2);
        long double mi=max(0ll,xx);
        if(u==v){

            
            if(xx<0){
                long double tt=(xx*xx-y*y)*1.0L/(2*xx);
                tt=max(tt,0.0L);
                tt=max(tt,1.0L*xx);
                ans=min(ans,sqrtl(y*y+tt*tt)/v);
            }
        }
        else if(u<v){
            long double tt=mi;
            
            if(dd>=0 ) tt=max(tt,a2); 
                ans=min(ans,sqrtl(y*y+tt*tt)/v);
        }
        else {
            if(dd>=0&&a2>mi-1e-7){
                
                long double tt=max(a1,mi);
                ans=min(ans,sqrtl(y*y+tt*tt)/v);
            } 
            
        }
        return ans;
    }
    
}
void solve()
{
    __int128 t;
    
    cin>>w>>x>>xx>>y>>u>>v;
    long double ans=1e9;
    ans=min(ans,deal(w,x,xx,y,u,v));
    x=-x;xx=-xx;
    swap(x,xx);
    u=-u;
    ans=min(ans,deal(w,x,xx,y,u,v));
    ans+=1.0L*(w-y)/v;
    cout<<fixed<<setprecision(10)<<ans<<'\n';
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

