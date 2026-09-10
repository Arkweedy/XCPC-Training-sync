#include<bits/stdc++.h>
#define N 509

using i64 = long long;
using ll = long long;

using namespace std;
int n,m;
bitset<512> dp[N][N];
bitset<512> a[N];
bitset<512> ans[N];
int vis[N];
bitset<512>  f[N];
bitset<512> sit[N];
void add(int i){

    bitset<512> k,s;
    s=dp[1][i];k[i]=1;

    for(int i=m;i;i--)
        if(s[i]==1){
            if(vis[i]){
                s^=f[i];
                k^=sit[i];
            }
            else {
                sit[i]=k;
                vis[i]=1;
                f[i]=s;
                return ;
            }
        }
}
void  deal(int x,int y){
    //return ;
    ans[x][y].flip();
    a[x][y].flip();
    a[x-1][y].flip();a[x+1][y].flip();
    a[x][y-1].flip();a[x][y+1].flip();
}
void cle(){
    for(int i=2;i<=n;i++)
        for(int j=1;j<=m;j++){
            //cout<<a[i-1][j]<<"LLL"<<endl;
            if(a[i-1][j]==1) deal(i,j);
        }
}
void pr(){
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++) cout<<a[i][j];
            cout<<'\n';
        }
}
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;cin>>c;
            if(c=='1') a[i][j]=1;
        }
    }
    //cout<<1;return ;
    for(int j=1;j<=m;j++) dp[n][j][j]=dp[n][j][j-1]=dp[n][j][j+1]=1,dp[n+1][j][j]=1;

    for(int i=n-1;i;i--)
        for(int j=1;j<=m;j++) {
            dp[i][j]=dp[i+1][j-1]^dp[i+1][j]^dp[i+1][j+1]^dp[i+2][j];
        }

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++) {
    //         cout<<i<<' '<<j<<endl;
    //         for(int k=1;k<=m;k++) cout<<dp[i][j][k];
    //         cout<<endl;
    //     }
    // }
//    cout<<1;return ;
    
    for(int i=1;i<=m;i++) add(i);
    //cout<<1;return ;
    cle();
    //pr();
//    cout<<1;return ;
    auto g=a[n];
    // for(int i=1;i<=m;i++) cout<<g[i];
    // cout<<endl;
//    for(int i=1;i<=m;i++) cout<<vis[i]<<endl;
    bitset<512> k;
    //    cout<<1;return ;
    for(int i=m;i;i--)
        if(g[i]){
            if(!vis[i]) {
cout<<"NO\n";return ;
            }
            else {
                g^=f[i];
                k^=sit[i];
            }
        }
    // for(int i=1;i<=m;i++) cout<<k[i];
    // cout<<endl;
    for(int i=1;i<=m;i++)
        if(k[i]) deal(1,i);
    //pr();
    cle();
        //cout<<1<<endl;return ;
    //pr();
    //cout<<1;return ;
    for(int i=1;i<=m;i++) assert(a[n][i]==0);

    cout<<"YES\n";
    for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++) cout<<ans[i][j];
            cout<<'\n';
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
