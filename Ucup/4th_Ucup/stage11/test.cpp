#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.20 10:35:36
constexpr int N =20;
int dp[N][N][N][N];
int can(int x,int y,int z,int w)
{
    if(x<0||y<0||z<0||w<0) return 0;
    int ans=1;
    if(x&&dp[x-1][y][z][w]==0) ans=0;
    if(y&&dp[x][y-1][z][w]==0) ans=0;
    if(z&&dp[x][y][z-1][w]==0) ans=0;
    if(w&&dp[x][y][z][w-1]==0) ans=0;
    return ans;
}
void solve()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        for(int k=0;k<N;k++) 
            for(int z=0;z<N;z++)
        {
            dp[i][j][k][z]=0;
            if(can(i-2,j,k,z)) dp[i][j][k][z]=1;
            if(can(i-3,j,k,z)) dp[i][j][k][z]=1;
            if(can(i,j-2,k,z)) dp[i][j][k][z]=1;
            if(can(i,j-3,k,z)) dp[i][j][k][z]=1;
            if(can(i,j,k-2,z)) dp[i][j][k][z]=1;
            if(can(i,j,k-3,z)) dp[i][j][k][z]=1;
            if(can(i,j,k,z-2)) dp[i][j][k][z]=1;
            if(can(i,j,k,z-3)) dp[i][j][k][z]=1;
            if(!dp[i][j][k][z]&&i!=1&&j!=1&&k!=1&&z!=1) 
            {
                if(i*j*k*z==0) continue;
                int cnt=0;
                if(i==2) cnt++;
                if(j==2) cnt++;
                if(k==2) cnt++;
                if(z==2) cnt++;
                
                if(cnt<2) cout<<4<<' '<<3<<endl,cout<<i<<' '<<j<<' '<<k<<' '<<z<<endl;
            }
        }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}