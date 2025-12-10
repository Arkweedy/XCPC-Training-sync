#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 2e5 + 10;

vector<int>f;

int find(int x){
    if(f[x] != x)f[x] = find(f[x]);
    return f[x];
}

void merge(int i,int j){
    i = find(i), j = find(j);
    if(i > j)swap(i,j);
    f[j] = i;
}

void solve()
{
    int n,m;cin>>n>>m;

    f.assign(n+1,0);
    iota(f.begin(),f.end(),0);

    vector<int>x(n+1,1);
    vector<vector<int>>e(n+1),ne(n+1);

    while(m--){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        ne[v].push_back(u);
    }      
    for(int i=1;i<=n;i++){
        for(int j=0;j+1<ne[i].size();j++){
            merge(ne[i][j],ne[i][j+1]);
        }
    }

    vector<int>dist(n+1,0);
    vector<vector<int>>adj(n+1),nadj(n+1);
    vector<int>deg(n+1);


    for(int i=1;i<=n;i++){
        for(auto j:e[i]){
            if(find(i) == find(j)){
                cout<<"No\n";
                return;
            }
            adj[find(i)].push_back(find(j));
            deg[find(j)]++;
        }
    }

    queue<int>q;
    q.push(1);
    dist[1] = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:adj[u]){
            dist[v] = max(dist[u]+1,dist[v]);
            deg[v]--;
            if(deg[v] == 0)q.push(v);
        }
    }

    for(int i=1;i<=n;i++){
        if(deg[i]){
            cout<<"No\n";
            return;
        }
    }
        // cout<<endl;
    for(int i=1;i<=n;i++){
        
        for(auto u: ne[i]){
            x[i] = dist[find(i)] - dist[find(u)];
        }
        //cout<<i<<' '<<x[i]<<endl;
    }

    fill(deg.begin(),deg.end(),0);

    for(int i=1;i<=n;i++){
        for(auto v:e[i]){
            deg[i]++;
        }
    }

    q.push(n);

    vector<ll>L(n+1),R(n+1);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:ne[u]){
            deg[v]--;
            if(deg[v] == 0)q.push(v);
        }
        if(!e[u].empty()){
            L[u] = 1e18; 
            for(auto v:e[u]){
                L[u] = min(L[u],L[v]);
                R[u] = max(R[u],R[v]);
            }
            L[u] += x[u],R[u] += x[u];
        }else{
            L[u] = x[u],R[u] = x[u];
        }
    }

    if(L[1] != R[1]){
        cout<<"No\n";
    }else{
        cout<<"Yes\n";
        for(int i=1;i<=n;i++)cout<<x[i]<<" \n"[i==n];
    }

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