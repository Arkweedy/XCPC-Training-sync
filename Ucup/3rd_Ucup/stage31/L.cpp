#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.24 11:12:01

void solve()
{
    int n, Q;
    cin >> n >> Q;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin >> s[i];
    }

    vector<vector<int>>rg(n * n * 4 + 1);
    //n * n * [r,u,l,d]
    //n * n * [r,f,l,b]
    //-1
    int outp = n * n * 4;

    array<int,4>dx = {0, -1, 0, 1}, dy = {1, 0, -1, 0};
    auto next = [&](int x, int y, int d, int t)->array<int,3>
    {
        int nd = (d + t - 1 + 4) % 4;
        int nx = x + dx[nd], ny = y + dy[nd];
        return array<int,3>{nx,ny,nd};
    };

    auto ok = [&](array<int, 3> p)->bool
    {
        int x = p[0], y = p[1], d = p[2];
        if(x >= 0 && y >= 0 && x < n && y < n && s[x][y] != '#')return true;
        else return false;
    };

    auto idx = [&](int x, int y, int d)->int
    {
        return x * n * 4 + y * 4 + d;
    };

    auto out = [&](int x, int y)->bool
    {
        if(x >= 0 && y >= 0 && x < n && y < n)return false;
        else return true;
    };

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(s[i][j] != '#'){
                for(int k = 0;k < 4;k++){
                    int p = idx(i, j, k);
                    for(int t = 0;t < 4;t++){
                        auto s = next(i,j,k,t);
                        if(ok(s)){
                            rg[idx(s[0],s[1],s[2])].push_back(p);
                            break;
                        }
                        else if(out(s[0],s[1])){
                            rg[outp].push_back(p);
                            break;
                        }
                    }
                }

            }
        }
    }

    queue<int>q;
    vector<int>dis(n * n * 4 + 1, -1);
    dis[outp] = 0;
    q.push(outp);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(auto s : rg[p]){
            if(dis[s] == -1){
                dis[s] = dis[p] + 1;
                q.push(s);
            }
        }
    }

    array<int, 256>mp;
    mp['R'] = 0;
    mp['U'] = 1;
    mp['L'] = 2;
    mp['D'] = 3;
    while(Q--){
        int x, y;
        char c;
        cin >> x >> y >> c;
        x--,y--;
        int d = mp[c];
        int p = idx(x, y, d);
        cout << dis[p] << "\n";
    }
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