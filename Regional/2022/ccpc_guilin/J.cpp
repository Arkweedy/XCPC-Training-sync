#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 2e5 + 10;
int n,m,p[N],ip[N];
vector<int> ve;//已经标号的点，值小到大
vector<int> nve;//无标号的值域
vector<int> e[N];
int in[N];
int ans[N];
int vis[N];
vector<int> pas;
void dfs(int p,int x)  //需要>num
{
    if(vis[p]&&p!=x)
    {
        return ;
    }
    vis[p]=1;
    pas.push_back(p);
    for(auto v:e[p])
    {
        dfs(v,x);
    }
}
vector<int> ne[N];
int viss[N];
void solve()
{
    cin>>n>>m;
    for(int i=0;i<=n;i++) ip[i]=-1;
    for(int i=1;i<=n;i++) 
    {
        cin>>p[i];
        if(p[i]==0) p[i]=-1;
    }
    p[0]=0;
    for(int i=0;i<=n;i++)
        if(p[i]>=0) ip[p[i]]=i;
    ve.clear();nve.clear();
//    cout<<ip[0]<<endl;
    //return ;
    for(int i=0;i<=n;i++) e[i].clear(),in[i]=0,ans[i]=vis[i]=viss[i]=0;

    for(int i=0;i<=n;i++)
        {
            if(ip[i]!=-1) ve.push_back(ip[i]),ans[ip[i]]=i;
            else nve.push_back(i);
        }

    
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        in[v]++;
    }

    for(int i=1;i<=n;i++)
        if(!in[i]) in[i]++,e[0].push_back(i);
    //for(auto p:ve) cout<<p<<endl;
    //cout<<endl;
    //for(auto p:nve) cout<<p<<endl;
    assert(ve.size());

    for(int i=0;i<=n;i++) in[i]=0;

    for(int i=ve.size()-1;i>=0;i--)
    {
        int g=ve[i];
        pas.clear();
        dfs(g,g);
        for(auto p:pas) ne[p].clear(),viss[p]=1;
        for(auto p:pas)
        {
            for(auto v:e[p])
                if(viss[v]) ne[p].push_back(v),in[v]++;
        }
        pas.clear();
        queue<int> q;q.push(g);
        while(q.size())
        {
            int p=q.front();q.pop();pas.push_back(p);
            for(auto v:ne[p])
            {
                in[v]--;
                if(!in[v]){q.push(v);}
            }
        }
        for(auto p:pas) viss[p]=0;
        while(pas.size()!=1) 
        {
            ans[pas.back()]=nve.back();
            pas.pop_back();nve.pop_back();
        }
    }
    for(int i=1;i<=n;i++)
        if(!ans[i]) assert(0);
    for(int i=1;i<=n;i++)
        for(auto v:e[i]) 
        {
            if(ans[i]>ans[v]) 
            {
                cout<<-1<<'\n';
                return ;
            }
        }
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}