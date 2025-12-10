#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    int t1 = c * 60 + d,t2  = e * 60 + f;
    array<array<int,60>,60>dis;
    for(auto arr : dis){
        arr.fill(-1);
    }
    auto in = [&](int x, int y)->bool
    {
        return (x * 60 + y) >= t1 && (x * 60 + y) <= t2;
    };
    auto ok = [&](int x, int y)->bool
    {
        return x >= 0 && x <12 && y >=0 && y < 60;
    };
    bitset<720>vs;
    queue<pair<int,int>>q;
    array<int,3>ans = {114514,-1,-1};
    array<int,4>dx = {1,-1,0,0},dy = {0,0,1,-1}, dd = {5,5,1,1};
    q.push({a,b});
    dis[a][b] = 0;
    vs[a*60 + b].flip();
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        if(in(x,y)){
            ans = min(ans,array<int,3>{dis[x][y],x,y});
        }
        //if(dis[x][y] > ans[0])break;
        for(int i = 0;i < 4;i++){
            int nx = (x + dx[i] + 12) % 12,ny = (y + dy[i] + 60) % 60;
            int pos = nx * 60 + ny;
            int nd = dis[x][y] + dd[i];
            if(!vs[pos]){
                dis[nx][ny] = dis[x][y] + dd[i];
                vs[pos].flip();
                q.push({nx,ny});
            }
        }
    }
    cout<<ans[1]<<" "<<ans[2]<<endl;
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