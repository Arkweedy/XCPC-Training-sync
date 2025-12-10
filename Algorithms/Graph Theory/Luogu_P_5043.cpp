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

void solve()
{
    int n;
    cin>>n;
    vector<ull>h(n);
    
    for(int i = 0;i < n;i++){
        int m;
        cin>>m;
        vector<vector<int>>g(m + 1);
        for(int i = 1;i <= m;i++){
            int p;
            cin>>p;
            if(p != 0){
                g[p].push_back(i);
                g[i].push_back(p);
            }
        }
    
        tree_hash t(g);
        t.calc(1);
        h[i] = t.unrooted_hash();
    }
    map<ull, int>fr, cnt;
    for(int i = n - 1;i >= 0;i--){
        fr[h[i]] = i + 1;
    }
    for(int i = 0;i < n;i++){
        cout<<fr[h[i]]<<endl;
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