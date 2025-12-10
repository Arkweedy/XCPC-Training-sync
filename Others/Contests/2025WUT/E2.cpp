#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr int P = 998244353;
//constexpr int P = 1000000007;
using Z = MInt<P>;
//using Z = double;

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    vector<Z>pos(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    for(int i = 0;i < n;i++){
        pos[i] = Z(a[i])/b[i];
    }

    vector<vector<int>>g(n);
    for(int i = 0;i < n-1;i++){
        int u, v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int root = 0;
    while(n != 2 && g[root].size() == 1)root++;
    constexpr int inf = 114514;
    vector<vector<int>>ng(n);
    vector<vector<Z>>dp(n);
    vector<int>fa(n, -1),dep(n,inf),sc(n, 0);
    vector<vector<vector<Z>>>pre(n),suf(n);
    vector<int>id(n);
    vector<int>isleaf(n, true);
    auto dfs = [&](auto&&self, int p)->void
    {
        ng[p].push_back(-1);
        for(auto s: g[p]){
            if(s != fa[p]){
                isleaf[p] = false;
                fa[s] = p;
                self(self, s); 
                ng[p].push_back(s);
                id[s] = ng[p].size() - 1;
                dep[p] = min(dep[p], dep[s] + 1);
                sc[p]++;
            }
        }
        if(isleaf[p])dep[p] = 1;  
        
        //calc
        dp[p].resize(dep[p] + 1);

        pre[p].resize(dep[p] + 1, vector<Z>(sc[p] + 1));
        suf[p].resize(dep[p] + 1, vector<Z>(sc[p] + 2));
        for(int j = 0;j < dep[p];j++){
            pre[p][j][0] = 1;
            suf[p][j][sc[p] + 1] = 1;
        }
        for(int i = 1;i < ng[p].size();i++){//idx 0 invalid 
            for(int j = 0;j < dep[p];j++){
                int s = ng[p][i];
                pre[p][j][i] = dp[s][j];
                pre[p][j][i] *= pre[p][j][i - 1];
                
            }
        }

        for(int i = sc[p];i > 0;i--){//idx 0 invalid 
            for(int j = 0;j < dep[p];j++){
                int s = ng[p][i];
                suf[p][j][i] = dp[s][j];
                suf[p][j][i] *= suf[p][j][i + 1];
            }
        }

        //dp[p][j] = (1 - pos)\prod dp[s][j] + p \prod dp[s][j - 1]
        for(int j = 0;j <= dep[p];j++){
            dp[p][j] = (1 - pos[p]) * suf[p][j][1] + (j > 0 ? pos[p] * suf[p][j - 1][1] : pos[p]);
        }
    };
    dfs(dfs,root);
    
    vector<vector<Z>>rdp(n, vector<Z>(n + 1));
    vector<vector<Z>>fdp(n, vector<Z>(n + 1));
    rdp[root] = dp[root];


    auto excp = [&](int p,int j)->Z
    {
        if(j < 0)return 1;
        else if(j >= pre[fa[p]].size())return 0;
        else return pre[fa[p]][j][id[p] - 1] * suf[fa[p]][j][id[p] + 1];
    };

    auto get_fdp = [&](int p, int j)->Z
    {
        if(j < 0)return 1;
        else if(j >= fdp[p].size())return 0;
        return fdp[p][j];
    };

    auto all = [&](int p, int j)->Z
    {
        if(j < 0)return 1;
        else if(j >= pre[p].size())return 0;
        else return pre[p][j][sc[p]];
    };

    auto rdfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                //calc rdp p
                if(p == root){
                    for(int j = 0;j < fdp[s].size();j++){
                        fdp[s][j] = (1 - pos[p]) * excp(s, j) + pos[p] * excp(s, j - 1);
                    }
                }
                else{
                    for(int j = 0;j < fdp[s].size();j++){
                        fdp[s][j] = (1 - pos[p]) * excp(s, j) * get_fdp(p, j) + pos[p] * excp(s, j - 1) * get_fdp(p, j - 1);
                    }
                }
                for(int j = 0;j <= n;j++){
                    rdp[s][j] = pos[s] * all(s, j - 1) * get_fdp(s, j - 1) + (1 - pos[s]) * all(s, j) * get_fdp(s, j);
                }

                self(self, s);
            }
        }
        return;
    };
    
    rdfs(rdfs,root);
    
    vector<Z>ans(n);
    
    for(int i = 0;i < n;i++){
        if(!isleaf[i] && n != 2){
            for(int j = 1;j <= n;j++){
                ans[i] += rdp[i][j];
            }
        }
        else{
            ans[i] = pos[i];
        }
    }
    
    for(int i = 0;i < n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
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