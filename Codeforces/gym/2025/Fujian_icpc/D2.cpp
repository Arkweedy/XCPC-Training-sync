#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct tree_hash
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

    static ull get(ull x)
    {
        //hash 1 random numberS
        // if(mp.count(x))return mp[x];
        // else return mp[x] = rng();

        //hash 2 poly
        return x * x + 1;
    }

private:
    

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

int lowbit(int x)
{
    return x & -x;
}

int bits(int x)
{
    int res = 0;
    while(x != 0){
        x >>= 1;
        res++;
    }
    return res;
}

void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    vector<pair<int,int>>e(n - 1);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
        if(u > v)swap(u,v);
        e[i] = {u,v};
    }
    
    
    tree_hash t(g);
    t.calc(0);
   
    auto &rdp  = t.rdp;
    auto &dp = t.dp;
    vector<ull>idp(n);
    
    auto build = [&](vector<vector<int>>&g, int n)->void
    {
        int len = 1 << n;
        g.resize(len);
        for(int i = 1;i < len / 2;i++){
            g[i].push_back(i*2);
            g[i*2].push_back(i);
            g[i].push_back(i*2+1);
            g[i*2+1].push_back(i);
        }
        return;
    };
    
    int x, y;
    if(lowbit(n + 2) == n + 2){
        x = y = bits(n + 2) - 1;
    }
    else{
        x = bits(lowbit(n + 2));
        y = bits(n + 2 - lowbit(n + 2));
    }
    
    vector<vector<int>>t1,t2;
    build(t1,x - 1);
    build(t2,y - 1);
    tree_hash th1(t1),th2(t2);
    th1.calc(1);
    th2.calc(1);
    set<ull>st1,st2;
    auto& rdp1 = th1.rdp, &rdp2 = th2.rdp;
    for(int i = 0;i < rdp1.size();i++){
        st1.insert(rdp1[i]);
    }
    for(int i = 0;i < rdp2.size();i++){
        st2.insert(rdp2[i]);
    }
    
    pair<int,int>res = {-1,-1};
    int ans = -1;

    auto dfs = [&](auto&&self ,int p, int fa)->void
    {
        if(p != 0){//check edge p-fa
            idp[p] = rdp[fa] - tree_hash::get(dp[p]);
            if((st1.count(dp[p]) && st2.count(idp[p]))||(st1.count(idp[p])&&st2.count(dp[p]))){
                res = {p, fa};
                return;
            }
        }
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
            }
        }
        return;
    };
    dfs(dfs, 0, -1);

    if(res.first > res.second)swap(res.first,res.second);
    for(int i = 0;i < n - 1;i++){
        if(res == e[i]){
            ans = i + 1;
        }
    }
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