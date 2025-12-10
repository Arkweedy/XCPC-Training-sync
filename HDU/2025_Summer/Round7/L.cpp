#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

class tree_hash
{
    static map<ull,ull>mp;
    static mt19937_64 rng;

    int n;
    vector<vector<int>>g;
    vector<ull>dp;
    vector<ull>rdp;//换根dp值
    int hash = 0;//整棵树hash值
    int calced;

public:
    tree_hash(vector<vector<int>>&ng)
    {
        n = ng.size();
        g = ng;
        dp.resize(n, 0);
        rdp.resize(n, 0);
    }

private:
    static ull get(ull x)
    {
        //hash 1 random number
        if(mp.count(x))return mp[x];
        else return mp[x] = rng();

        //hash 2 poly
        return x * x + 1;
    }

    void dfs(int p, int fa)
    {
        for(auto s : g[p]){
            if(s != fa){
                dfs(s,p);
                dp[p] += get(dp[s]);
            }
        }
        dp[p]++;
        return;
    };

    void rdfs(int p, int fa)
    {
        if(fa == -1){
            rdp[p] = dp[p];
        }else{
            rdp[p] = dp[p] + get(rdp[fa] - get(dp[p]));
        }
        for(auto s : g[p]){
            if(s != fa){
                rdfs(s, p);
            }
        }
        return;
    };

public:
    void calc(int root = 0)
    {
        calced = true;
        dfs(root, -1);
        rdfs(root, -1);
        for(int i = 0;i < n;i++){
            hash ^= rdp[i];
        }
    }

    ull rooted_hash(int p)
    {
        assert(calced);
        return rdp[p];
    }

    ull unrooted_hash()
    {
        assert(calced);
        return hash;
    }

};
//非const 的static 类成员需要类外初始化
mt19937_64 tree_hash::rng(chrono::steady_clock::now().time_since_epoch().count());
map<ull,ull> tree_hash::mp;

constexpr ull P = 998244353;

void solve()
{
    int m;
    cin>>m;
    vector<int>fa(m);
    vector<vector<int>>g(m);
    for(int i = 1;i < m;i++){
        cin>>fa[i];
        fa[i]--;
        g[fa[i]].push_back(i);
    }

    tree_hash th(g);
    th.calc();

    vector<int>rnk(m);

    auto cmp = [&](auto&&self, int i, int j)->bool
    {
        while(th.rooted_hash(i) == th.rooted_hash(j) && !g[i].empty()){
            i = g[i][0];
            j = g[j][0];
        }
        if(th.rooted_hash(i) == th.rooted_hash(j))return th.rooted_hash(i) < th.rooted_hash(j);
        else {
            for(int k = 0;k < g[i].size() && k < g[j].size();k++){
                if(th.rooted_hash(g[i][k]) != th.rooted_hash(g[j][k])){
                    return self(self, g[i][k], g[j][k]);
                }
            }
            return g[i].size() < g[j].size();
        }
    };

    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            self(self, s);
        }
        sort(g[p].begin(),g[p].end(),[&](int i, int j)->bool
        {
            return cmp(cmp, i, j);
            //return i < j;//        
        });
        for(int i = 0;i < g[p].size();i++){
            rnk[g[p][i]] = i + 1;
        };

    };

    int n = 0;
    vector<ull>ans;
    auto calc = [&](auto&&self, int p, ull prefix, string ss)->void
    {
        if(g[p].empty()){
            n++;
            ans.push_back(prefix);
            cerr<<ss<<endl;
            return;
        }
        int w = 1;
        for(auto s : g[p]){
            self(self, s, prefix * P + w, ss + char('0' + w));
            w++;
        }
    };

    calc(calc,0,0,"");

    cout<<n<<endl;
    for(int i = 0;i < n;i++){
        cout<<ans[i]<<endl;
    }
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