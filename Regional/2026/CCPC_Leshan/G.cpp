#include <bits/stdc++.h>
#define N 100009
#define ls p<<1
#define rs p<<1|1
#define mod 998244353

using ll = long long;
using i64 = long long;

using namespace std;
struct mat{
    int a[2][2];
    mat(){
        memset(a,0,sizeof(a));
    }
    
};
mat operator *(mat a,mat b){
    mat c;
    for(int k=0;k<2;k++)
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++) c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mod;
    return c;
}
int n,q;
int x[N],a[N];
mat tr[N<<2];
void upd(int p,int l,int r,int x,mat ma){
    if(l==r){
        tr[p]=ma;return ;
    }
    int m=l+r>>1;
    if(x<=m) upd(ls,l,m,x,ma);
    else upd(rs,m+1,r,x,ma);
    tr[p]=tr[ls]*tr[rs];
}
void update(int p){
    if(p<2) return ;
    if(p>n) return ;
    mat g;
    g.a[0][1]=1;
    int len=x[p]-x[p-1];
    if(len>=a[p]) g.a[0][0]=1;
    if(len>=a[p-1]) g.a[1][1]=1;
    if(len>=a[p]+a[p-1]) g.a[1][0]=1;
    upd(1,2,n,p,g);

}
int que(){
    if(n==1) return 2;
    int ans=0;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++) ans=(ans+tr[1].a[i][j])%mod;
    return ans;
}
void solve()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=2;i<=n;i++) update(i);

    cout<<que()<<'\n';
    while(q--){
        int p,v;cin>>p>>v;
        a[p]=v;
        update(p);update(p+1);
        cout<<que()<<'\n';
    }


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