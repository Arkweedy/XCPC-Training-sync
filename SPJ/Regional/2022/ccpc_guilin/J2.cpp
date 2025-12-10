#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

const int N = 2e5 + 10;

vector<int>e[N];
int R[N],p[N],n,m,deg[N],L[N];
bool vis[N];

void dfs(int u){
    if(vis[u])return;
    vis[u] = 1;
    if(p[u])R[u] = p[u];
    for(auto v:e[u]){
        dfs(v);
        R[u] = min(R[u],R[v]);
    }
}

void solve()
{
    cin>> n >> m;
    set<int>s;
    for(int i=1;i<=n;i++){
        e[i].clear();
        R[i] = n + 1,L[i] = 0;
        vis[i] = 0;
        s.insert(i);
        deg[i] = 0;
    }

    for(int i=1;i<=n;i++){
        cin>>p[i];
        s.erase(p[i]);
    }

    while(m--){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        deg[v]++;
    }

    for(int i=1;i<=n;i++)if(!vis[i])dfs(i);

    priority_queue<pair<int,int>>heap;
    for(int i=1;i<=n;i++)if(deg[i] == 0)heap.push({-R[i],i});

    while(!heap.empty()){
        auto [_,u] = heap.top();
        heap.pop();
        
        // cout<<u<<' '<<L[u]<<' '<<R[u]<<endl;
        if(p[u] == 0){
            auto it = s.upper_bound(L[u]);
            if(it == s.end()){
                cout<<-1<<'\n';
                return;
            }
            p[u] = (*it);
        }

        if(p[u] > R[u]){
            cout<<-1<<'\n';
            return;
        }

        s.erase(p[u]);

        for(auto v:e[u]){
            deg[v]--,L[v] = max(L[v],p[u]);
            if(deg[v] == 0)heap.push({-R[v],v});
        }
    }

    for(int i=1;i<=n;i++)cout<<p[i]<<" \n"[i==n];
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