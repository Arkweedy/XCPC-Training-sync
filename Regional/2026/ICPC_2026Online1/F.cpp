#include <bits/stdc++.h>
using namespace std;
int a[100009];
void solve()
{
    int n,m;
    int ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x;cin>>x;
            a[i]+=x;
        }
        if(a[i]<a[i-1]) ans++;
    }
    cout<<ans;
}
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}