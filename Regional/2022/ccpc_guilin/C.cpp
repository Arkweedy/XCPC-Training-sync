#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int mod=1000000007;
constexpr int K=3;
struct mat{int a[K][K];};
mat operator *(mat a,mat b)
{
    mat c;
    memset(c.a,0,sizeof(c.a));
    for(int i=0;i<K;i++)
        for(int k=0;k<K;k++)
            for(int j=0;j<K;j++)  c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mod;
    return c;
}
struct vec{int a[K];};
vec operator *(mat a,vec b)
{
    vec c;memset(c.a,0,sizeof(c.a));
    for(int i=0;i<K;i++)
        for(int j=0;j<K;j++) c.a[i]=(c.a[i]+(1ll*a.a[i][j]*b.a[j]))%mod;
    return c;
}
int n,m;
int a[N];
mat aa[N];//qp(a,i);
mat s1={
    4,0,0,
    1,2,0,
    1,0,2,
};
mat s2={
    4,0,0,
    1,1,1,
    1,1,1
};
vec st;
int sl[N],sr[N];
int pl,pr;
void print(mat a)
{
    for(int i=0;i<K;i++)
    {
        for(int j=0;j<K;j++) cout<<a.a[i][j]<<' ';
        cout<<endl;
    }
}
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) sl[i]=sl[i-1]+a[i],sl[i]%=mod,pl=(pl+sl[i])%mod;
    for(int i=n;i;i--) sr[i]=sr[i+1]+a[i],sr[i]%=mod,pr=(pr+sr[i])%mod;

    st={1ll*n*sl[n]%mod,pl,pr};
    for(int i=0;i<K;i++) aa[0].a[i][i]=1;
    for(int i=1;i<=m;i++) aa[i]=aa[i-1]*s1;
    int ans=0;
    for(int i=1;i<=m+1;i++)
    {
        mat lin=aa[i-1];
        if(i<=m) lin=s2*lin,lin=aa[m-i]*lin;
        //print(lin);
        //cout<<endl;
        vec con=lin*st;
    //    cout<<con.a[1]<<endl;
        ans=max(ans,con.a[1]);
    }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
//    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}