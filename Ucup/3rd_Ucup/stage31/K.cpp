#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.24 10:25:35
int a[100],n,nn,vis[100];
int sit[100],cnt;//答案
string s;
vector<int> v;
char mp[2]={'.','#'};
int cal=0;
void dfs(int now,int p,int sum)
{
//    cout<<now<<p<<endl;
    //cal++;
    if(sum>=cnt) return ;
    if(now>=v.size()) {
        cnt=sum;
        for(int i=1;i<v.size();i++) sit[i]=vis[i];
        return ;
    }
    vis[now]=p;
    if(vis[now]<v[now]) return ;
    if(vis[now]==0)
    {
        for(int d=1;d<=100;d++)
        {
            int j=now-d,jj=now-2*d;
            if(jj<=0) break;
            if(vis[j]+vis[jj]+vis[now]==0) return ;
        }
    }
    dfs(now+1,0,sum);dfs(now+1,1,sum+1);
}
void solve()
{
    cin>>s;
    n=s.length();
    if(n==1)
    {
        cout<<1<<'\n';
        cout<<"#";
        return ;
    }
    s=' '+s;
    for(int i=1;i<=n;i++) 
        if(s[i]=='#') a[i]=1;
    //for(int i=1;i<=n;i++) cout<<a[i]<<endl;
    pair<int,string > ans={100,""};
    for(int j=0;j<2;j++)
    {
        v.clear();v.push_back(0);
        int con=0;
        cnt=100;
        for(int i=1;i<=n;i++) 
            {
                if(i%2==j) v.push_back(a[i]);
                else con++;
            }
        //for(int i=1;i<v.size();i++) cerr<<v[i]<<endl;
        dfs(1,0,con);dfs(1,1,con+1);
        string ss;
        int c=0;
        for(int i=1;i<=n;i++)
            {
                if(i%2==j)  ss+=mp[sit[++c]];
                else ss+=mp[1];
            }

        ans=min(ans,{cnt,ss});
    }
    cout<<ans.first<<'\n';
    cout<<ans.second;
    //cerr<<cal<<endl;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}