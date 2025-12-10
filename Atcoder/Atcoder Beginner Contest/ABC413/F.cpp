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
    int k;
    cin>>k;
    vector<vector<int>>vs(n,vector<int>(m));
    vector<vector<int>>dis(n,vector<int>(m));
    queue<pair<int,int>>q;
    for(int i = 0;i < k;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        dis[u][v] = 0;
        vs[u][v] = 2;
        q.push({u,v});
    }
    
    int dx[] = {1,0,-1,0},dy[] = {0,1,0,-1};
    auto ok = [&](int x, int y)->bool
    {
        return x >= 0 && x < n && y >= 0 && y < m && vs[x][y] < 2;
    };
    while(!q.empty()){
        const auto& [x,y] = q.front();
        q.pop();
        for(int i = 0;i < 4;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(ok(nx,ny)){
                vs[nx][ny]++;
                if(vs[nx][ny] == 2){
                    dis[nx][ny] = dis[x][y] + 1;
                    q.push({nx,ny});
                }
            }
        }
    }

    ll sum = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            sum += dis[i][j];
        }
    }
    cout<<sum<<endl;
    return;
    

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}