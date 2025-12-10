#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,st;
    cin>>n >> st;
    st--;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    if(st == 0){
        cout<<0<<endl;
        return;
    }

    vector<int>best(n);
    vector<int>dis(n, -1);
    vector<int>vs(n);
    auto dfs = [&](auto&&self, int p, int fa,int state)->void
    {
        if(state == 0){
            vs[p] = 1;
            if(a[p] == 1){
                for(auto s : g[p]){
                    if(s != fa){
                        if(a[s] == 1){
                            best[p] = 1;
                            self(self,p,fa,1);
                            return;
                        }
                    }
                }
                for(auto s : g[p]){
                    if(s != fa){
                        self(self, s, p, 0);
                    }
                }
            }
            else{
                for(auto s : g[p]){
                    if(s != fa){
                        if(a[s] == 1){
                            self(self, s, p, 0);
                        }
                    }
                }
            }
        }
        else{
            dis[p] = 0;
            for(auto s : g[p]){
                if(s != fa){
                    self(self,s,p,1);
                }
            }
        }
    };
    dfs(dfs,st,-1,0);


    queue<int>q;
    for(int i = 0;i < n;i++){
        if(best[i]){
            q.push(i);
        }
    }

    while(!q.empty()){
        int p = q.front();
        q.pop();
        
        for(auto s : g[p]){
            if(vs[s] && dis[s] == -1){//can arrive
                dis[s] = dis[p] + 1;
                q.push(s);
            }
        }
    }

    //prefix min on tree
    vector<int>pa = a;
    vector<int>pamin(n);
    vector<int>steps(n,0);
    auto dfs2 = [&](auto&&self, int p, int fa)->void
    {
        for(auto s : g[p]){
            if(s != fa){
                if(dis[s] == -1){
                    dis[s] = dis[p];
                }
                else{
                    dis[s] = min(dis[s],dis[p]);
                }
                pa[s] += pa[p];
                pamin[s] = min(pamin[p],pa[s]);
                steps[s] = steps[p] + 1;
                self(self,s,p);
            }
        }
    };
    dfs2(dfs2,st,-1);

    vector<int>time(n);
    auto dfs3 = [&](auto&&self, int p, int fa)->void
    {
        for(auto s : g[p]){
            if(s != fa){
                time[s] = time[p] + 1;
                self(self, s, p);
            }
        }
    };
    dfs3(dfs3,0,-1);
    
    int ans = 0;
    for(int i = 0;i < n;i++){
        int usetime = steps[i];
        if(pamin[i] < 0){
            int rounds = (abs(pamin[i]) + 1) / 2;
            if(dis[i] == -1)continue;
            else usetime += rounds * 2 + dis[i] * 2;
        }
        if(usetime < time[i]){
            int suvtime = usetime + (time[i] - usetime - 1) / 2 * 2;
            ans = max(ans, suvtime);
        }
    }

    cout<<ans + 1<<endl;
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