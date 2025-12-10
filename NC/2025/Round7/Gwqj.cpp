#include<bits/stdc++.h>
#define N 1000009
#define M 998244353
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using ll=long long ;
using namespace std;
int p[N],a[N],f[N],cnt;
void solve()
{
    for(int i=2;i<N;i++)
    {
        if(!a[i]) p[++cnt]=i,f[i]=1;
        for(int j=1;1ll*p[j]*i<N;j++)
        {
            a[i*p[j]]=1;
            f[i*p[j]]=f[i]^1;
            if(!(i%p[j])) break;
        }
    }
    for(int i=2;i<100;i++) 
    {
        if(f[i] == 1)cerr<<i<<" ";
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int tt=1;
   // cin>>tt;
    while(tt--) solve();
    return 0;
}