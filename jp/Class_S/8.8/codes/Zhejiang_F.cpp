#include<bits/stdc++.h>

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

void solve()
{
    int n, m, k;
    cin>>n >> m >> k;
    vector<int>c(n);
    vector<vector<int>>cp(50);
    for(int i = 0;i < n;i++){
        cin>>c[i];
        c[i]--;
        cp[c[i]].push_back(i);
    }
    vector<vector<int>>g(n);
    for(int i = 0; i< m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        //g[v].push_back(u);
    }

    //cerr<<"test : "<<endl;
    constexpr int inf = 1e9;
    auto check = [&](int clr)->bool
    {
        auto checkbit = [&](int b, int isinv)->bool
        {
            int s = n,t = n + 1;
            vector<int>dis(n + 2, inf);
            vector<int>vs(n + 2);
            vector<int>buf;
            dis[s] = 0;
            g.emplace_back();
            g.emplace_back();
            for(int j = 0;j < cp[clr].size();j++){
                int p = cp[clr][j];
                if((j >> b & 1) == isinv){
                    g[s].push_back(p);
                    //cerr<<"s to "<<p<<endl;
                }else{
                    g[p].push_back(t);
                    buf.push_back(p);
                    //cerr<<p<<" to t"<<endl;
                }
            }

            //bfs
            queue<int>q;
            q.push(s);
            vs[s] = 1;
            while(!q.empty()){
                auto p = q.front();
                q.pop();
                for(auto x :g[p]){
                    if(!vs[x]){
                        vs[x] = true;
                        dis[x] = dis[p] + 1;
                        q.push(x);
                    }
                }
            }
            g.pop_back();
            g.pop_back();
            for(auto x : buf){
                g[x].pop_back();
            }
            // if(!(dis[t] - 1 > k)){
            //     cerr<<clr<<" "<<b <<" "<<isinv<<endl;
            //     cerr<<dis[t]<<endl;
            // }
            return (dis[t] - 1 > k);
        };
        int res = 1;
        for(int i = 0;(1 << i) < cp[clr].size();i++){
            res &= checkbit(i,0);
            res &= checkbit(i,1);
        }
        return res;
    };

    int ans = 1;
    for(int i = 0;i < 50;i++){
        ans &= check(i);
    }
    cout<< (ans ? "YES" : "NO")<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin>>t;
    while(t--)solve();
    return 0;
}
