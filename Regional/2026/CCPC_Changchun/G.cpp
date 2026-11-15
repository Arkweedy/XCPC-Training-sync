#include<bits/stdc++.h>
#define N 200009

using ll = long long;
using i64 = long long;

using namespace std;
struct EBCC{
    int n;
    vector<vector<int> > adj;
    vector<int> stk;
    vector<int> dfn,low,bel;
    int cur,cnt;

    EBCC(int n){init(n);}

    void init(int n){
        this->n=n;
        adj.assign(n,{});
        dfn.assign(n,-1);
        low.resize(n);
        bel.assign(n,-1);
        stk.clear();
        cnt=cur=0;
    }

    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int x,int p){
        dfn[x]=low[x]=cur++;
        stk.push_back(x);
        int num=0;

        for(auto y:adj[x]){
            if(y==p){
                if(!num) num++;
                else low[x]=min(low[x],dfn[p]);
                continue;
            }

            if(dfn[y]==-1){
                dfs(y,x);
                low[x]=min(low[x],low[y]);
            }
            else if(bel[y]==-1&&dfn[y]<dfn[x]){
                low[x]=min(low[x],dfn[y]);
            }
        }
        


        if(dfn[x]==low[x]){
            int y;
            do{
                y=stk.back();
                bel[y]=cnt;
                stk.pop_back();
            }while(y!=x);

            cnt++;
        }
    }

    void build(){
        for(int i=0;i<n;i++) 
            if(dfn[i]==-1) dfs(i,-1);
    }
    

};
int a[N];
int c[N];
int u[N],v[N];
vector<int> e[N];
int g[N],d[N],vis[N];
void dfs(int p,int fa){
    vis[p]=1;
    if(fa==-1) d[p]=0;
    else d[p]=d[fa]+1;
    for(auto v:e[p]){
        if(v==fa) continue;
        dfs(v,p);
        g[p]^=g[v];
    }
}
void solve()
{
    int n,m;
    cin>>n>>m;
//    cout<<n<<' '<<m<<endl;
    for(int i=0;i<=n+1;i++ ) a[i]=c[i]=g[i]=d[i]=vis[i]=0,e[i].clear();
    for(int i=1;i<=n;i++) {
        char c;cin>>c;
        a[i]^=(c=='1');
    }
    for(int i=1;i<=n;i++) {
        char c;cin>>c;
        a[i]^=(c=='1');
    }

    int s=0;
    for(int i=1;i<=n;i++) {
        c[i]=a[i]^a[i-1];
        s^=c[i];
    }
    
    c[n+1]=s;

    // for(int i=1;i<=n+1;i++) cout<<c[i]<<' ';
    // cout<<endl;
    EBCC  ebcc(n+1);
    for(int i=1;i<=m;i++){
        cin>>u[i]>>v[i];
        v[i]++;
        ebcc.addEdge(u[i]-1,v[i]-1);
    }
    ebcc.build();

    for(int i=1;i<=n+1;i++){
      // cout<<i<<' '<<ebcc.bel[i-1]<<endl;
        int j=i-1;
        g[ebcc.bel[j]]^=c[i];
    }
    

    ebcc.build();

    int nn=ebcc.cnt;
    for(int i=1;i<=m;i++){
        int uu=u[i],vv=v[i];
        uu--;vv--;
        uu=ebcc.bel[uu],vv=ebcc.bel[vv];
        if(uu==vv) continue;
        e[uu].push_back(vv);
        e[vv].push_back(uu);
    }
//    for(int i=0;i<nn;i++) cout<<g[i]<<endl;
    int err=0;
    for(int i=0;i<nn;i++)
        if(!vis[i]) {
            dfs(i,-1);
            if(g[i]) err=1;
        }
//    for(int i=0;i<nn;i++) cout<<g[i]<<endl;
    
    //cout<<err<<"err"<<endl;

    for(int i=1;i<=m;i++){
        if(err) cout<<0;
        else {
            int uu=u[i],vv=v[i];
            uu--;vv--;
            uu=ebcc.bel[uu],vv=ebcc.bel[vv];
            if(uu==vv) cout<<1;
            else {
                if(d[uu]<d[vv]) swap(uu,vv);
                if(g[uu]==0) cout<<1;
                else cout<<0;
            }
        }
    }   
    cout<<'\n';



}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}