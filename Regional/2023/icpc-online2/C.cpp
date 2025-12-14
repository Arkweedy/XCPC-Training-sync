#include<bits/stdc++.h>
#define N 100009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using namespace std;
using ll =long long ;
const ll INF =1e18;
const int mod=998244353;

struct TwoSat{
    int n;
    vector<vector<int>>e;
    vector<int>ans;
    TwoSat(int n):n(n),e(2*n),ans(n){}

    void add(int u,int v){
        e[u].push_back(v);
    }

    bool work(){
        vector<int>id(2*n,-1),dfn(2*n,-1),low(2*n,-1);
        vector<int>stk;
        int tot = 0,cnt = 0;
        auto dfs = [&](auto &&self,int u)->void{
            stk.push_back(u);
            dfn[u] = low[u]=tot++;
            for(auto v:e[u]){
                if(dfn[v]==-1){
                    self(self,v);
                    low[u] = min(low[u],low[v]);
                }else if(id[v]==-1){
                    low[u] = min(low[u],dfn[v]);
                }
            }
            
            if(dfn[u]==low[u]){
                int v;
                do{
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                }while(v!=u);
                cnt++;
            }
        };
        for(int i=0;i<2*n;i++){
            if(dfn[i]==-1){
                dfs(dfs,i);
            }
        }
        for(int i=0;i<n;i++){
            if(id[2*i]==id[2*i+1])return 0;
            ans[i] = id[2*i] > id[2*i+1];
        }
        return 1;
    }
};

void solve()
{
    int n;cin>>n;
    vector<int>a(n),c(n-1);
    for(int i=0;i<n;i++)cin>>a[i];
    int m = n - 1;
    int tot = 0;
    map<pair<int,int>,int>ha;
    for(int i=0;i<m;i++){
        auto t = make_pair(a[i],a[i+1]);
        if(!ha.count(t))ha[t] = tot++;
        c[i] = ha[t];
    }
    vector<vector<int>>e(tot);
    for(int i=0;i<m;i++)e[c[i]].push_back(i);
    
    vector<pair<int,int>>edges;
    edges.push_back({2*0,2*0+1});
    edges.push_back({2*(m-1),2*(m-1)+1});
    for(int i=0;i+1<m;i++){
        int j = i+1;
        edges.push_back({2*i,2*j+1});
        edges.push_back({2*j,2*i+1});   
    }
    for(int i=0;i<tot;i++){
        if(e[i].size()>1){
            int pre = m++;
            edges.push_back({2*pre,2*e[i][0]});
            for(int j=1;j<e[i].size();j++){
                int cur = m++;
                edges.push_back({2*e[i][j]+1,2*pre});
                edges.push_back({2*cur,2*e[i][j]});
                edges.push_back({2*cur,2*pre});
            }
            pre = m++;
            int j = e[i].size() - 1;
            edges.push_back({2*pre,2*e[i][j]});
            j--;
            while(j>=0){
                int cur = m++;
                edges.push_back({2*e[i][j]+1,2*pre});
                edges.push_back({2*cur,2*e[i][j]});
                edges.push_back({2*cur,2*pre});
                j--;
            }
        }
    }
    TwoSat sol(m);
    for(auto [u,v]:edges)sol.add(u,v);//cout<<u<<' '<<v<<endl;
    if(sol.work()){
        vector<int>c;
        for(int i=0;i<n-1;i++){
            if(sol.ans[i])c.push_back(i+1);
        }
        cout<<c.size()<<'\n';
        for(auto k:c)cout<<k<<' ';
        cout<<'\n';
    }
    else cout<<"NO\n";
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    while(tt--) solve();
    return 0;
}