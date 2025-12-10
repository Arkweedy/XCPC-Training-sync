#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using namespace std;

constexpr int N = 1e5 + 10;

template<typename T>
pair<T,T> operator+(const pair<T,T>&lhs, const pair<T,T>&rhs)
{
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

template<typename T>
pair<T,T> operator-(const pair<T,T>&lhs, const pair<T,T>&rhs)
{
    return make_pair(lhs.first - rhs.first, lhs.second - rhs.second);
}

struct tree_hash{
    int n;
    static constexpr int P1 = 1;
    static constexpr int P2 = 1e9 + 9;
    vector<vector<int>>g;
    vector<pair<ll,ll>>dp;
    vector<pair<ll,ll>>rdp;

    tree_hash(const vector<vector<int>>ng)
    {
        n = ng.size();
        g = ng;
        dp.resize(n, {});
        rdp.resize(n, {});
    }

    static pair<ll,ll> get(pair<ll,ll> x)
    {
        return make_pair(x.first * x.first + 1 % P1, x.second + x.second + 1 % P2);
    }

    static void norm(pair<ll,ll>& x)
    {
        x.first = (x.first % P1 + P1) % P1;
        x.second = (x.second % P2 + P2) % P2;
    }

    void dfs(int p, int fa)
    {
        dp[p] = {1,1};
        for(auto s : g[p]){
            if(s != fa){
                dfs(s, p);
                dp[p] = dp[p] + get(dp[s]);
                norm(dp[p]);
            }
        }
    }

    void rdfs(int p, int fa)
    {
        if(fa == -1){
            rdp[p] = dp[p];
        }
        else{
            auto x = rdp[fa] - get(dp[p]);
            norm(x);
            rdp[p] = dp[p] + get(x);
            norm(rdp[p]);
        }

        for(auto s : g[p]){
            if(s != fa){
                rdfs(s, p);
            }
        }
    }

    void calc(int root = 0)
    {
        dfs(root, -1);
        rdfs(root, -1);
    }

};

void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tree_hash h1(g);
    h1.calc();
    auto& g1 = h1.rdp;
    vector<int>ord(n);
    iota(ord.begin(),ord.end(), 0);
    sort(ord.begin(),ord.end(),[&](int i, int j)->bool
    {
        return g1[i] < g1[j];
    });
    int root = ord[0];
    tree_hash h2(g);
    h2.calc(root);
    auto &f2 = h2.dp;
    for(auto& vec : g){
        sort(vec.begin(),vec.end(),[&](int i, int j)->bool
        {
            return f2[i] < f2[j];
        });
    }
    int tot = 1;
    vector<int>ans(n + 1);
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        ans[tot++] = p + 1;
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
            }
        }
        return;
    };
    dfs(dfs, root, -1);

    for(int i = 1;i <= n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return;

}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
