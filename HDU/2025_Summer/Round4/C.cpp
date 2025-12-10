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
    vector<vector<array<int,3>>>g(n);
    set<int>st;
    int isinit = -0;
    for(int i = 0;i < n;i++){
        int u,v,x,y;
        cin>>u>>v>>x>>y;
        u--,v--;
        g[u].push_back({v,x,y});
        g[v].push_back({u,y,x});
    }
    vector<int>sz(n, 1);
    auto dfs1 = [&](auto&&self, int p, int fa)->void
    {
        for(const auto& [s,u,v]: g[p]){
            if(s != fa){
                self(self,s,p);
                //calc
                //u+v, su - u + v, sv - v + u, n - u - v
                int x = min(u + v, n - u - v), y = min(n - sz[s] - u + v, sz[s] - v + u);
                if(isinit){
                    set<int>nst;
                    if(st.count(x))nst.insert(x);
                    if(st.count(y))nst.insert(y);
                    st = move(nst);
                }
                else{
                    isinit = true;
                    st.insert(x);
                    st.insert(y);
                }
                
                sz[p] += sz[s];
            }
        }
    };

    if(st.size() == 0){
        cout<<0<<endl;
        return;
    }

    //calc
    for(auto sum : st){
        //cnt 0 = sum 
        
    }
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