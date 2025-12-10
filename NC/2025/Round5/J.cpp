#include<bits/stdc++.h>
#define N 200009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
const int INF=1e9;
using ll =long long ;
using ld =long double ;
using namespace std;
int dd[4][2]={1,0,-1,0,0,1,0,-1};
int n,m;
int check(int x,vector<vector<int> > &d)
{
    int ma1=-INF,ma0=-INF,mi1=INF,mi0=INF;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(d[i][j]<=x) continue;
            cnt++;
            ma1=max(ma1,i+j);
            mi1=min(mi1,i+j);
            ma0=max(ma0,i-j);
            mi0=min(mi0,i-j);
        }
    }
    if(!cnt) return 1;
    int ans=max(ma1-mi1,ma0-mi0);
    ans=(ans+1)/2;
    return ans<=x;
}
void solve()
{
    cin>>n>>m;
    vector<vector<int> > a(n+1,vector<int> (m+1));
    vector<vector<int> > d(n+1,vector<int> (m+1,INF));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    queue<pair<int,int> > q;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==1)
            {
                d[i][j]=0;
                q.push({i,j});
            }
        }
    }
   
    while(q.size())
    {
        auto [x,y]=q.front();q.pop();
        for(int i=0;i<4;i++)
        {
            int xx=x+dd[i][0],yy=y+dd[i][1];
           // cerr<<xx<<yy<<endl;
            if(xx<1||xx>n||yy<1||yy>m) continue;
            if(d[xx][yy]==INF)
            {
                d[xx][yy]=d[x][y]+1;
                q.push({xx,yy});
            }
        }
    }
   // return ;
    int l=-1,r=n+m;
    while(r-l>1)
    {
        int mm=l+r>>1;
        if(check(mm,d)) r=mm;
        else l=mm;
    }
    cout<<r;
    return;
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    //cin>>tt;
    while(tt--)
    {
        solve();
    }
    return 0;
}