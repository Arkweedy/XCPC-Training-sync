#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class Euler_graph_dir
{
    int n;
    vector<vector<int>>g;
    vector<int>indeg,outdeg;
    vector<int>cur;
    pair<int,int>odd_deg;

    void Hierholzer(int p)
    {
        for(auto&i = cur[p];i < g[p].size();){
            int s = g[p][i];
            i++;
            Hierholzer(s);
        }
        ans.push_back(p);
    }

public:
    vector<int>ans;//stack

    Euler_graph_dir(int n_)
        :n(n_),odd_deg(-1,-1)
    {
        g.resize(n);
        indeg.resize(n);
        outdeg.resize(n);
        cur.resize(n);
    }

    void add_edge(int u,int v)
    {
        g[u].push_back(v);
        indeg[v]++;
        outdeg[u]++;
    }

    bool check_euler()
    {
        int ok = 1;
        for(int i = 0;i < n;i++){
            ok &= (indeg[i] == outdeg[i]);
        }
        return ok;
    }

    bool check_semi_euler()
    {
        int eq = 0,gre = 0,les = 0;
        for(int i = 0;i < n;i++){
            if(indeg[i] == outdeg[i]){
                eq++;
            }else if(indeg[i] + 1 == outdeg[i]){
                odd_deg.first = i;
                les++;
            }else if(indeg[i] == outdeg[i] + 1){
                odd_deg.second = i;
                gre++;
            }else{
                return false;
            }
        }
        return (eq == n - 2 && gre == 1 && les == 1) || (eq == n);
    }

    void get_euler_path()
    {
        if(!check_semi_euler())return;
        if(odd_deg.first != -1){
            Hierholzer(odd_deg.first);
        }
        else{
            for(int i = 0;i < n;i++){
                if(!g[i].empty()){
                    Hierholzer(i);
                    break;
                }
            }
        }
        reverse(ans.begin(),ans.end());
    }

    void get_euler_circuit()
    {
        if(!check_euler())return;
        for(int i = 0;i < n;i++){
            if(!g[i].empty()){
                Hierholzer(i);
                break;
            }
        }
        reverse(ans.begin(),ans.end());
    }

    void min_lexicographical()
    {
        for(auto& vec : g)
        {
            sort(vec.begin(),vec.end());
        }
    }
};

void solve()
{
    int n, m;
    cin>>n>>m;
    Euler_graph_dir g(n + 1);
    for(int i  = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        g.add_edge(u,v);
    }
    g.min_lexicographical();
    g.get_euler_path();
    auto&ans = g.ans;
    if(ans.empty()){
        cout<<"No"<<endl;
    }else{
        for(int i = 0;i < m + 1;i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
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