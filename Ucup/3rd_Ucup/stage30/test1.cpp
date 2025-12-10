#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int mod =1e9+7;
#define K 20
struct mat{int a[K][K];};
mat operator *(mat a,mat b)
{
    mat c;
    for(int i=0;i<K;i++)
        for(int j=0;j<K;j++)
        {
            c.a[i][j]=0;
            for(int k=0;k<K;k++) c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mod;
        }
    return c;
}
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
    mat ans;
    mat a;
    mat b;
    for(int i=0;i<K;i++)
        for(int j=0;j<K;j++) a.a[i][j]=b.a[i][j]=0;
    for(int i=0;i<K;i++) a.a[i][0]=1;
    for(int i=0;i<K-1;i++) a.a[i][i+1]=b.a[i][i+1]=1;
    for(int i=0;i<K;i++)
        for(int j=0;j<K;j++) ans.a[i][j]=(i==j);
    for(int i=1;i<=50;i++)
    {
        ans=ans*a;
        print(ans);
        cout<<endl;
    }
    ans=ans*b;
    for(int i=1;i<=50;i++)
    {
        ans=ans*a;
        print(ans);
        cout<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
   // cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
