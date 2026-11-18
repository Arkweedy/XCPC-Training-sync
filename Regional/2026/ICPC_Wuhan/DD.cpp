#include<bits/stdc++.h>
#define N 200009

using ll = long long;
using i64 = long long;

using namespace std;
int a[N],vis[N];
vector<int> e[N];
int d[N];
void dfs(int p,int dd){
    
    d[p]=dd;
    vis[p]=1;
    for(auto v:e[p]){
        if(vis[v]) continue;
        dfs(v,dd+1);
    }
}
void solve()
{
    int n,m;
    cin>>n>>m;
    int cnt=0,err=0;
    int st=-1;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(a[i]==0) cnt++;
        if(a[i]==0) st=i;
    }
    if(cnt!=1) err=1;


    for(int i=1;i<=n;i++){
        int t;cin>>t;
        for(int j=1;j<=t;j++){
            int x;cin>>x;
            e[i].push_back(x);
        }
    }

    for(int i=1;i<=n;i++){
        sort(e[i].begin(),e[i].end(),[&](int i,int j){return a[i]<a[j];});
    }

    
    
    if(err){
        cout<<-1<<'\n';
        return ;
    }

    dfs(st,0);
//    cout<<2<<endl;return ;

    for(int i=1;i<=n;i++){
        if(a[i]!=d[i]) err=1;
    }

    if(err){
        cout<<-1<<'\n';
        return ;
    }


    cout<<st<<'\n';
    for(int i=1;i<=n;i++){
        for(auto p:e[i]) cout<<p<<' ';
        cout<<'\n';
    }


}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}