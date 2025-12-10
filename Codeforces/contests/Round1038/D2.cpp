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

    constexpr int inf = 1145141919;
    vector<vector<int>>vs(n),wait(n),time(n);
    for(int i = 0;i < n;i++){
        vs[i].resize(deg[i]);
        wait[i].resize(deg[i], inf);
        time[i].resize(deg[i], inf);
    }
    queue<pair<int,int>>q;
    q.push({0,0});//node,time
    vs[0][0] = 0;
    wait[0][0] = 0;
    time[0][0] = 0;
    while(!q.empty()){
        auto [p,k] = q.front();
        q.pop();
        int t = time[p][k], w = wait[p][k];
        int s = g[p][k];
        int x = (t + 1) % deg[s];
        int y = (t + 1) % deg[p];
        //wait
        if(!vs[p][y]){
            vs[p][y] = 1;
            time[p][y] = t + 1;
            wait[p][y] = w + 1;
            q.push({p, y});
        }
        else if(time[p][y] == t + 1){
            wait[p][y] = min(wait[p][y], w + 1);
        }

        //next
        if(!vs[s][x]){
            vs[s][x] = 1;
            time[s][x] = t + 1;
            wait[s][x] = w;
            q.push({s,x});
        }
        else if(time[s][x] == t + 1){
            wait[s][x] = min(wait[s][x], w);
        }
    }
    
    int anst = inf, answ = inf;
    for(int i = 0;i < deg[n - 1];i++){
        if(anst > time[n-1][i]){
            anst = time[n-1][i];
            answ = wait[n - 1][i];
        }
        else if(anst == time[n - 1][i]){
            answ = min(answ,wait[n - 1][i]);
        }
    }
    cout<<anst<<" "<<answ<<endl;
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