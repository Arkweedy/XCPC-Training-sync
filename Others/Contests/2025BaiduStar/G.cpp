#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Info
{
    int x, y;
    int id;
    array<int,4>ex;
    Info(int a, int b, int c, int d)
    {
        ex = {0,0,0,0};
        x = a, y = b, ex[c] = 1, id = d;
    }
};

struct SCC{
    int n;
    vector<vector<int>>e;
    vector<int>stk;
    vector<int>dfn, low, bel;
    int cur = 0, cnt = 0;

    SCC(){}
    SCC(int n):n(n),e(n),dfn(n, -1),low(n),bel(n, -1){}
    void add(int u, int v){
        cerr << "add edge " << v << " -> " << u << endl;
        e[u].push_back(v);
    }

    void dfs(int x)
    {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        for(auto y : e[x]){
            if(dfn[y] == -1){
                dfs(y);
                low[x] = min(low[x], low[y]);
            }
            else if(bel[y] == -1){
                low[x] = min(low[x], dfn[y]);
            }
        }
        if(dfn[x] == low[x]){
            int y;
            do{
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            }while(y != x);
            cnt++;
        }
    }

    void build()
    {
        for(int i = 0;i < n;i++){
            if(dfn[i] == -1){
                dfs(i);
            }
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int>x(n),y(n);
    map<int,map<int,int>>no;
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i];
        no[x[i]][y[i]] = 1;
    }
    
    map<int,map<int,int>>mpx, mpy;
    array<int,4>dx = {1,0,-1,0}, dy = {0,1,0,-1};

    //self 


    vector<Info>pos(1, {0,0,0,0});
    mpx[0][0] = 0;
    mpy[0][0] = 0;
    pos[0].ex[0] = 0;
    int tot = 1;

    auto add = [&](int x, int y)->void
    {
        for(int i = 0;i < 4;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(no[nx].count(ny)){
                continue;
            }
            if(!mpx[nx].count(ny) ){
                mpx[nx][ny] = tot;
                mpy[ny][nx] = tot;
                pos.emplace_back(nx,ny,i,tot);
                tot++;
            }
            else{
                pos[mpx[nx][ny]].ex[i] = 1;
            }
        }
    };

    for(int i = 0;i < n;i++){
        add(x[i], y[i]);
    }

    for(int i = 0;i < tot;i++){
        cerr << pos[i].id << " " << pos[i].x << " "<< pos[i].y << endl;
    }


    // for(int i = 0;i < tot;i++){
    //     cerr << pos[i].ex[0] << " " << pos[i].ex[1] << " "<< pos[i].ex[2] << " " << pos[i].ex[3] << endl;
    // }

    //barry pos : 
    //0 l 
    //1 d
    //2 r
    //3 u
    
    SCC scc(tot);

    int a0 = -1,a1 = -1,a2 = -1,a3 = -1;
    //col d->u
    int flg = 0;
    for(auto &[x, mp] : mpx){
        int pre = -1;
        for(auto &[y, id] : mp){
            if(flg = 1){
                int tmp = pre;
                pre = 0;
                if(!pos[pre].ex[3] && !pos[id].ex[1] && pos[id].ex[3]){
                    scc.add(id,pre);
                }
                //now -> pre u-> d
                if(!pos[id].ex[1] && !pos[pre].ex[3] && pos[pre].ex[1]){
                    scc.add(pre,id);
                }
                pre = tmp;
            }
            if(pre != -1){
                //pre -> now d->u
                if(!pos[pre].ex[3] && !pos[id].ex[1] && pos[id].ex[3]){
                    scc.add(id,pre);
                }
                //now -> pre u-> d
                if(!pos[id].ex[1] && !pos[pre].ex[3] && pos[pre].ex[1]){
                    scc.add(pre,id);
                }
            }
            if(x == 0 && y == 0){
                //a1 = pre;
                flg = 1;
            }
            if(pre != -1 && pos[pre].x ==0 && pos[pre].y == 0){
                a3 = id;
            }
            if(pos[id].ex[1] || pos[id].ex[3])
                pre = id;
        }
    }
    //row l->r
    for(auto &[y, mp] : mpy){
        int pre = -1;
        for(auto &[x, id] : mp){
            if(flg == 1){
                int tmp = pre;
                pre = 0;
                if(!pos[pre].ex[2] && !pos[id].ex[0] && pos[id].ex[2]){
                    scc.add(id,pre);
                }
                //now -> pre u-> d
                if(!pos[id].ex[0] && !pos[pre].ex[2] && pos[pre].ex[0]){
                    scc.add(pre,id);
                }
                pre = tmp;
            }
            if(pre != -1){
                //pre -> now l->r
                if(!pos[pre].ex[2] && !pos[id].ex[0] && pos[id].ex[2]){
                    scc.add(id,pre);
                }
                //now -> pre u-> d
                if(!pos[id].ex[0] && !pos[pre].ex[2] && pos[pre].ex[0]){
                    scc.add(pre,id);
                }
            }
            if(x == 0 && y == 0){
                a0 = pre; 
            }
            if(pre != -1 && pos[pre].x ==0 && pos[pre].y == 0){
                a2 = id;
            }
            if(pos[id].ex[0] || pos[id].ex[2]){
                pre = id;
                flg = 0;
            }
        }
    }

    // if(!pos[0].ex[0] && !pos[0].ex[2] && a0 != -1 && a2 != -1){
    //     if(!pos[a0].ex[2] && !pos[a2].ex[0] && pos[a2].ex[2]){
    //         scc.add(a2,a0);
    //     }
    //     //now -> pre u-> d
    //     if(!pos[a2].ex[0] && !pos[a0].ex[2] && pos[a0].ex[0]){
    //         scc.add(a0,a2);
    //     }
    // }

    // if(!pos[0].ex[1] && !pos[0].ex[3] && a1 != -1 && a3 != -1){
    //     if(!pos[a1].ex[3] && !pos[a3].ex[1] && pos[a3].ex[3]){
    //         scc.add(a3,a1);
    //     }
    //     //now -> pre u-> d
    //     if(!pos[a3].ex[1] && !pos[a1].ex[3] && pos[a1].ex[1]){
    //         scc.add(a1,a3);
    //     }
    // }

    

    scc.build();

    //cerr << pos.size() << " " << scc.cnt << endl;

    auto&bel = scc.bel;
    auto&e = scc.e;
    int cnt = scc.cnt;
    vector<int>sz(cnt);
    vector<vector<int>>g(cnt);
    vector<int>indeg(cnt);
    for(int i = 0;i < tot;i++){
        int u = bel[i];
        sz[u]++;
        for(auto x : e[i]){
            int v = bel[x];
            if(u == v)continue;
            g[u].push_back(v);
            indeg[v]++;
        }
    }

    vector<int>res(cnt);
    queue<int>q;
    for(int i = 0;i < cnt;i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int p = q.front();
        q.pop();
        res[p] += sz[p];
        for(auto s : g[p]){
            res[s] = max(res[s], res[p]);
            indeg[s]--;
            if(indeg[s] == 0){
                q.push(s);
            }
        }
    }

    int ans = res[bel[0]];
    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt ;
    while(tt--){
        solve();
    }
    return 0;
}