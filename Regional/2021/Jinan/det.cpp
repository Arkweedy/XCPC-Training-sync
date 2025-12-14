#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=612;
int p;
int ksm(int x,int y)
{
    int r=1;
    while (y)
    {
        if (y&1) r=(ll)r*x%p;
        y>>=1;x=(ll)x*x%p;
    }
    return r;
}
int cal(int a[][N],int n)
{
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)a[i][j] %= p;
    }
    int i,j,k,r=1,fh=0,l;
    for (i=1;i<=n;i++)
    {
        for (j=i;j<=n;j++) if (a[j][i]) break;
        if (j>n) return 0;
        if (i!=j) swap(a[j],a[i]),fh^=1;
        r=(ll)r*a[i][i]%p;
        k=ksm(a[i][i],p-2);
        for (j=i;j<=n;j++) a[i][j]=(ll)a[i][j]*k%p;
        for (j=i+1;j<=n;j++)
        {
            a[j][i]=p-a[j][i];
            for (k=i+1;k<=n;k++) a[j][k]=(a[j][k]+(ll)a[j][i]*a[i][k])%p;
            a[j][i]=0;
        }
    }
    if (fh) return (p-r)%p;
    return r;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,i,j;
    static int a[N][N];
    cin>>n >> p;
    for (i=1;i<=n;i++) for (j=1;j<=n;j++) cin>>a[i][j];
    cout<<cal(a,n)<<endl;
}
/*
3
3 1 4
1 5 9
2 6 5
998244263
*/