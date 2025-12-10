#include<bits/stdc++.h>
#define N 2009
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using namespace std;

int n,m,c[N][N],num[N];
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>c[i][j];
    for(int j=1;j<=m;j++)
    {
        int k=2;
        int a=c[1][j];
        while(k<=n&&c[k][j]==a) k++;
        num[a]=max(num[a],k-1);
    }
    int ans=n*m;
    for(int i=1;i<=m;i++) ans-=num[i];
    cout<<ans;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}