#include<bits/stdc++.h>
#define N 200009

using ll = long long;
using i64 = long long;

using namespace std;
int a[N],vis[N];
vector<int> e[N],ve[N];
int f[N];
int ok[N];
int num;
int find(int p){
    if(f[p]!=p) f[p]=find(f[p]);
    return f[p];
}
void merge(int a,int b){
    a=find(a);b=find(b);
    if(a==b) return ;
    f[a]=b;
    num--;
}
void add(int p){
    ok[p]=1;
    num++;
    for(auto v:e[p]){
        if(ok[v]){merge(p,v);};
    }
}
void solve()
{
    int n,m;
    cin>>n>>m;
    num=0;
    for(int i=1;i<=n;i++) f[i]=i;
    int err=0,cnt=0,maxd=0;
    int st=-1;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(a[i]==0) cnt++;
        maxd=max(maxd,a[i]);
        vis[a[i]]++;
        if(a[i]==0) st=i;
        ve[a[i]].push_back(i);
    }
    if(cnt!=1) err=1;
    for(int i=0;i<=maxd;i++){
        if(!vis[i]) err=1;
    }
    for(int i=1;i<=n;i++){
        int t;cin>>t;
        for(int j=1;j<=t;j++){
            int x;cin>>x;
            e[i].push_back(x);
        }
    }
    map<int,int> mp;
    for(int i=maxd;i>=0;i--){
        for(auto p:ve[i]){
            add(p);
        }
        mp.clear();
        for(auto p:ve[i]){
            int g=find(p);
            if(mp[g]) err=1;
            mp[g]=1;
        }
        if(ve[i].size()!=num) err=1;
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