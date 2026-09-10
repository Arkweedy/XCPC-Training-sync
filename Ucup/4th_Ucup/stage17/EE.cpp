#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;
int f[100][30][30];
int vis[3];
void solve()
{

    for(int i=0;i<pow(3,18);i++)

    
    {
    //    cout<<i<<endl;
        vector<int> ve;
        int jj=i;
        for(int j=0;j<18;j++) ve.push_back({jj%3}),jj/=3;

        for(int ii=1;ii<=2;ii++)
            for(int j=0;j<3;j++) 
                for(int jj=0;jj<3;jj++)
                f[ii][j][jj]=ve[(ii-1)*9+j*3+jj];
            int can=1;
        for(int a=0;a<3;a++)
            for(int b=0;b<3;b++)
                for(int c=0;c<3;c++)
                    for(int d=0;d<3;d++)
                    {
                        if(!can) break;
                    
                        if(f[1][d][b]==a) continue;
                        if(f[2][a][c]==b) continue;
                        

                        can=0;


                        
                    }
            if(can) {
                for(int i=1;i<=2;i++)
                    for(int j=0;j<3;j++)
                        for(int k=0;k<3;k++)  cout<<f[i][j][k]<<endl;
                cerr<<1;return ;}
            

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
