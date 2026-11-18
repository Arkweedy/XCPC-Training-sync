#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

constexpr int P = 998244353;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n),b(n);
    vector<int>f(n);
    vector<vector<int>>g(n);
    for(int i = 1;i < n;i++){
        int x;
        cin >> x;
        x--;
        f[i] = x;
    }
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
    }

    vector<int>indeg(n),outdeg(n);
    for(int i = 1;i < n;i++){
        int p = f[i];
        if(a[p] >= b[i] && b[p] >= a[i]){
            //
        }
        else if(a[p] < b[i]){//p first
            //cerr << "add " << p << " " << i << endl;
            g[p].push_back(i);
            g[i].push_back(p);
            outdeg[p]++;
            indeg[i]++;
        }
        else if(b[p] < a[i]){// i first
            //cerr << "add " << i << " " << p << endl;
            g[i].push_back(p);
            g[p].push_back(i);
            outdeg[i]++;
            indeg[p]++;
        }
    }

    vector<int>fac(n + 1),invfac(n + 1);
    fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n] = power(fac[n], P - 2);
    for(int i = n - 1;i >= 0;i--){
        invfac[i] = 1ll *invfac[i + 1] * (i + 1) % P;
    }

    auto binom = [&](int n, int m)->int
    {
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };
    

    vector<int>vs(n);
    vector<int>node;

    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        vs[p] = 1;
        node.push_back(p);
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
            }
        }
    };

    vector<int>sz(n, 0);

    auto calc = [&](auto&&self, int p, int fa)->int
    {
        int res = 1;
        for(auto s : g[p]){
            if(s != fa){
                int rs = self(self, s, p);
                sz[p] += sz[s];
                res = 1ll * res * rs % P * binom(sz[p], sz[s]) % P;
            }
        }
        sz[p]++;
        return res;
    };

    int ans = fac[n];
    for(int i = 0;i < n;i++){
        if(!vs[i]){
            dfs(dfs, i, -1);
            int ip = -1, op = -1;
            int ci = 0, co = 0;
            for(auto x : node){
                
                if(indeg[x] == 0){
                    ci++;
                    ip = x;
                }
                if(outdeg[x] == 0){
                    co++;
                    op = x;
                }
            }

            if(ci == 1){//outer
                int res = calc(calc, ip, -1);
                ans = 1ll * ans * res % P;
                ans = 1ll * ans * invfac[sz[ip]] % P;
            }
            else{//inner
                int res = calc(calc, op, -1);
                ans = 1ll * ans * res % P;
                ans = 1ll * ans * invfac[sz[op]] % P;
            }

            node.clear();
        }
    }

    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}