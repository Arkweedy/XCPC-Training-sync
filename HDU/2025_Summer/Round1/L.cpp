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
    cerr<<"Cases on n = "<<n<<endl;
    map<multiset<int>,multiset<int>>mp;
    map<int,multiset<int>>f;
    map<int,vector<int>>g;
    auto next = [&](multiset<int>s)-> multiset<int>
    {
        multiset<int>ns;
        for(auto x : s){
            if(x > 1){
                ns.insert(x - 1);
            }
        }
        ns.insert(s.size());
        return ns;
    };    
    
    multiset<int>s0;
    map<multiset<int>,int>id;
    int tot = 0;

    auto get = [&](auto&&self, multiset<int>&st, int rem)->void
    {
        if(rem == 0){
            mp[st] = next(st);
            if(!id.count(st)){
                id[st] = ++tot;
                f[id[st]] = st;
            }
        }
        for(int i = 1;i <= rem;i++){
            st.insert(i);
            self(self,st,rem - i);
            st.extract(i);
        }
        return;
    };

    get(get,s0,n);

    

    auto print = [&](multiset<int>s)->void
    {
        for(auto x : s){
            cerr<<x<<" ";
        }
        cerr<<endl;
    };
    
    map<multiset<int>,int>onloop;
    
    auto add_Edge = [&](int u, int v)->void
    {
        g[u].push_back(v);
        g[v].push_back(u);
    };


    for(auto [st,nx] : mp){
        add_Edge(id[st],id[nx]);
        //cerr<<id[st]<<" "<<id[nx]<<endl;
    }

    vector<int>vs(tot + 1);

    
    
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        if(vs[p]){
            auto s = f[p];
            if(onloop[s])return;
            cerr<<"circle:"<<endl;
            int len = 0;
            do{
                len++;
                print(s);
                onloop[s] = 1;
                s = next(s);
            }while(s != f[p]);
            cerr<<"len = "<<len<<endl;
        }
        else{
            vs[p] = 1;
            for(auto s : g[p]){
                if(s != fa)
                    self(self,s, p);
            }
        }
        return;
    };
   
    for(auto [st,nx] : mp){
        if(!vs[id[st]]){
            dfs(dfs,id[st], -1);
        }
    }
    
    
    // map<multiset<int>,int>vs2;
    // for(auto [st, nx] : mp){
    //     if(onloop[st] && !vs2[st]){
    //         cerr<<"find a circle!"<<endl;
    //         int len = 0;
    //         auto p = st;
    //         do{
    //             len++;
    //             print(p);
    //             vs2[p] = 1;
    //             p = next(p);
    //         }while(st != p);
    //         cerr<<"len = "<<len<<endl;
    //     }
    // }


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