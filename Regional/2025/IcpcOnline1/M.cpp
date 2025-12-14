#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e4 + 10;

ll d[N];

struct edge{
    int u,v;
}t[N];

vector<pair<int,int>>e[N];

void dfs(int u,int f,ll dist){
    d[u] = dist;
    for(auto [v,w]:e[u]){
        if(v==f)continue;
        dfs(v,u,dist + w);
    }
}

int n,m;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
void solve()
{
    cin>>n>>m;
    for(int i=0;i<n-1;i++){
        int u,v,w;cin>>u>>v>>w;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    
    for(int i=0;i<m;i++){
        cin>>t[i].u>>t[i].v;
    }
    
    dfs(1,0,0);

    shuffle(t,t+m,rng);
    priority_queue<pair<ll,int>>heap;
    
    ll sum = 0;
    for(int i=1;i<=n;i++)sum += d[i];
    cout<<sum<<'\n';
    for(int i=0;i<n-1;i++){
        
        for(int i=0;i<m;i++){
            auto [u,v] = t[i];
            if(d[u] < d[v])heap.push({-d[u],v});
            else if(d[v] < d[u])heap.push({-d[v],u});
        }
        
        while(!heap.empty()){
            auto [cur,u] = heap.top();
            heap.pop();
            cur = -cur;
            if(cur >= d[u])continue;
            d[u] = cur;
            for(auto [v,w]:e[u]){
                if(d[v] > d[u] + w){
                    heap.push({-d[u]-w,v});
                }
            }
        }
        
        sum = 0;
        for(int i=1;i<=n;i++)sum += d[i];
        cout<<sum<<'\n';
    }
    sum = 0;
    for(int i=1;i<=n;i++)sum += d[i];
    cout<<sum<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;;
    while(t--){
        solve();
    }
    return 0;
}
