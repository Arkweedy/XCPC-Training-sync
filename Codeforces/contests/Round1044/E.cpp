#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n + 1);
    for(int i = 1;i <= n - 1;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    constexpr int inf = 1145141919;
    //vector<vector<array<int,3>>>dp(n + 1,{inf,inf,inf});
    // 0 -> not choose ,not cut
    // 1 -> choose
    // 2 -> not choose ,cut

    vector<int>cut;
    vector<int>becut(n + 1);
    vector<int>deg(n + 1);
    for(int i = 1;i <= n;i++){
        deg[i] = g[i].size();
    }

    int root = 1;

    auto dfs = [&](auto&&self, int p, int fa)->int // son is choose ? 
    // 0 -> not choose
    // 1 -> choose
    // 2 -> must choose, not choose
    {
        int must = 0;
        int state;
        for(auto s : g[p]){
            if(s != fa){
                int res = self(self, s, p);
                if(res == 0){
                    continue;
                }
                else if(res == 1){
                    deg[p]--;
                }
                else if(res == 2){
                    must = 1;
                }
            }
        }

        if(must || deg[p] >= 4){
            state = 1;
        }
        else if(deg[p] == 3){
            state = 2;
        }
        else{
            state = 0;
        }
        if(state == 1 || (state == 2 && p == root)){
            becut[p] = 1;
            cut.push_back(p);
        }
        return state;
    };

    dfs(dfs, root, -1);

    vector<vector<int>>ng(n + 1);
    for(int i = 1;i <= n;i++){
        for(auto s : g[i]){
            if(!becut[i] && !becut[s]){
                ng[i].push_back(s);
            }
        }
    }

    vector<int>op1;
    vector<int>vs(n + 1);
    auto dfs2 = [&](auto&&self, int p, int fa)->void
    {
        if(vs[p])return;
        vs[p] = 1;
        op1.push_back(p);
        for(auto s : ng[p]){
            if(s != fa){
                self(self, s, p);
            }
        }
    };

    for(int i = 1;i <= n;i ++){
        if(ng[i].size() <= 1){//find from list head
            dfs2(dfs2,i,-1);
        }
    }

    int opt = cut.size() + op1.size();
    int upper = n * 5 / 4;
    cout<<cut.size() + op1.size()<<endl;
    assert(opt <= upper);
    for(int i = 0;i < cut.size();i++){
        cout<<2<<" "<<cut[i]<<"\n";
    }
    for(int i = 0;i < n;i++){
        cout<<1<<" "<<op1[i]<<"\n";
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    int cnt = 0;
    // if(tt == 10000){
    //     while(tt--){
    //         cnt++;
    //         int n;
    //         cin>>n;
    //         vector<pair<int,int>>e;
    //         for(int i = 0;i < n -1;i++){
    //             int u,v;
    //             cin>>u>>v;
    //             e.emplace_back(u,v);
    //         }
    //         if(cnt == 30){
    //             cout<<n<<endl;
    //             for(auto [u,v]:e){
    //                 cout<<u<<" "<<v<<endl;
    //             }
    //         }
    //     }
    // }
    // else
    while(tt--){
        solve();
    }
    return 0;
}