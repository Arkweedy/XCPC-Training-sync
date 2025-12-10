#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    vector<int>deg(n);
    for(int i= 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    
    // max n + m steps 
    constexpr int inf = 1145141919;
    vector<vector<int>>vs(n);
    vector<vector<int>>wait(n);
    vector<vector<int>>time(n);
    for(int i = 0;i < n;i++){
        vs[i].resize(deg[i]);
        wait[i].resize(n, inf);
        time[i].resize(n, inf);
    }
    queue<array<int,3>>q;// point, time, wait 
    q.push({0,0,0});
    
    int ans = inf;
    int wans = inf;
    wait[0][0] = 0;
    time[0][0] = 0;
    vs[0][0] = 1;
    while(!q.empty()){
        auto [p, t, ww]  = q.front();
        q.pop();
        
        int nx = t % deg[p];
        int w = wait[p][nx];
        int s = g[p][nx];
        int x = (t + 1) % deg[s];
        int y = (t + 1) % deg[p];

        if(!vs[s][x]){
            vs[s][x] = 1;
            time[s][x] = t + 1;
            wait[s][x] = w;
            q.push({s,t+1,w});
        }
        else{
            if(time[s][x] == t + 1){
                wait[s][x] = min(wait[s][x], w);
            }
        }

        if(!vs[p][y]){
            vs[p][y] = 1;
            time[p][y] = t + 1;
            wait[p][y] = w + 1;
            q.push({p,t+1,w+1});
        }
        else{
            if(time[p][y] == t + 1){
                wait[p][y] = min(wait[p][y], w + 1);
            }
        }
    }
    
    for(int i = 0;i < deg[n - 1];i++){
        int t = time[n - 1][i], w = wait[n - 1][i];
        if(t < ans){
            ans = t;
            wans = w;
        }
        else if(t == ans){
            wans = min(wans, w);
        }
    }

    cout<<ans<<" "<<wans<<endl;
    return;
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