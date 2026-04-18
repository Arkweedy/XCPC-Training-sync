#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;

using namespace std;
vector<long double > ve,v;
long double a[100];
void dfs(int p,long double f){

    if(p>23){
        ve.push_back(f);return ;
    }
    dfs(p+1,f);
    long double ff=f+a[p];
    dfs(p+1,ff);
}
void solve()
{ 
    int cnt=0;
    // for(int i=2;i<=6;i++){
    //     for(int j=1;j<i;j++) a[++cnt]=1.0L*i/j;
    // }
    // for(int i=7;i<=13;i++) a[++cnt]=1.0L/i;
    for(int i=2;i<=10;i++) a[++cnt]=1.0L/i;
    for(int i=21;i<=100;i+=5) a[++cnt]=1.0L/i;
    //cout<<cnt<<endl;
    long double a=0;
    dfs(2,0);
    ve.push_back(0);ve.push_back(1);
    sort(ve.begin(),ve.end());
    long double  ma=0;
    for(int i=0;i+1<ve.size();i++) ma=max(ma,ve[i+1]-ve[i]);
    cout<<ma<<endl;
//    return ;
   cout<<ve.size()<<endl;
     ma=0;
     long double ans=1;
    for(int i=1;i<=5000;i++){
        long double d=sqrtl(i);
        d=d-(int)d;
        //cerr<<d<<endl;
    //    cerr<<d<<endl;
        if(sqrt(i)*sqrt(i)==i) continue;
        ans=min(ans,d);
        auto it=lower_bound(ve.begin(),ve.end(),d);
        long double s=1;
        s=min(s,fabsl(*it-d));
        it--;
        s=min(s,fabsl(*it-d));
        ma=max(ma,s);
        v.push_back(ma);
    }
     sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    cout<<v[0]<<endl;
    // for(auto p:v) cerr<<p<<endl;
    //cout<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}