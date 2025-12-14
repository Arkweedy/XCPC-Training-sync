#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.26 22:21:20

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }

    vector<multiset<int>>as(n),bs(n);
    vector<int>azcnt(n),bzcnt(n);

    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1; i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }


    auto adda = [&](int p, int v)->void
    {
        if(v == 0)azcnt[p]++;
        else if(bs[p].find(v) != bs[p].end())bs[p].extract(v);
        else as[p].insert(v);
    };

    auto addb = [&](int p, int v)->void
    {
        if(v == 0)bzcnt[p]++;
        else if(as[p].find(v) != as[p].end())as[p].extract(v);
        else bs[p].insert(v);
    };

    string ans(n,'0');

    auto dfs2 = [&](auto&&self, int p,int fa)->void
    {
        //add self
        adda(p,a[p]);
        addb(p,b[p]);

        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);

                if(as[p].size() + bs[p].size() < as[s].size() + bs[s].size()){
                    swap(as[p],as[s]);
                    swap(bs[p],bs[s]);
                }

                for(auto x : as[s]){
                    adda(p, x);
                }
                for(auto x : bs[s]){
                    addb(p, x);
                }
                azcnt[p] += azcnt[s];
                bzcnt[p] += bzcnt[s];
            }
        }
        //cerr<<p<<" "<<as[p].size()<<" "<<bs[p].size()<<" "<<azcnt[p]<<" "<<bzcnt[p]<<endl;
        // for(auto x :as[p]){
        //     cerr<<x<<" ";
        // }
        // cerr<<endl;
        if(as[p].size() <= bzcnt[p] && bs[p].size() <= azcnt[p]){
            ans[p] = '1';
        }
        assert(as[p].size() + azcnt[p] == bs[p].size() + bzcnt[p]);
        return;
    };

    dfs2(dfs2, 0,-1);

    cout<<ans<<endl;
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