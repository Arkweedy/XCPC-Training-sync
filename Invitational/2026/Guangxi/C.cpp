#include<bits/stdc++.h>

using namespace std;

using i64 = long long;
using ll = long long;

int lowbit(int x)
{
    return x & -x;
}

constexpr int P = 1e9 + 7;

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

struct DSU{
    int n;
    vector<char>fa, sz;
    vector<char>iscir;
    vector<char>val;
    i64 ok = 1;
    

    DSU(int n_)
    {
        n = n_;
        fa.resize(n);
        sz.resize(n, 1);
        iscir.resize(n);
        val.resize(n);
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    int merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv){
            if(iscir[fu]){
                ok = 0;
                val[fu] = 0;
            }
            else{
                iscir[fu] = 1;
                val[fu] = 2;
            }
            return false;
        }
        if(sz[fu] < sz[fv])swap(fu, fv);
        fa[fv] = fu;
        sz[fu] += fv;
        if(iscir[fu] && iscir[fv]){
            ok = 0;
            val[fu] = 0;
        }
        else if(iscir[fu] || iscir[fv]){
            iscir[fu] = 1;
            val[fu] = 2;
        }
        else{
            val[fu] = val[fu] + val[fv] - 2;
        }
        return true;
    }

    void activate(int p, int d)
    {
        val[p] = d;
    }

    int siz(int p)
    {
        return sz[find(p)];
    }

    i64 calc(int mask)
    {
        if(!ok)return 0;
        i64 res = 1;
        for(int i = 0;i < n;i++){
            if(find(i) == i && ((mask >> i) & 1)){
                res *= val[i];
            }
        }
        return res;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>a(n, vector<int>(n));
    vector<int>d(n);
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        a[u][v] = 1;
        a[v][u] = 1;
        d[u]++;
        d[v]++;
    }
    
    //cerr << "OK" << endl;

    int len = 1 << n;
    vector<int>in(len), popc(len);
    vector<DSU>dsu(len, n);
    for(int i = 1;i < len;i++){
        int p = __lg(lowbit(i));
        in[i] = in[i ^ (1 << p)];
        popc[i] = popc[i ^ (1 << p)] + 1;
        dsu[i] = dsu[i ^ (1 << p)];
        dsu[i].activate(p, d[p]);
        for(int j = p + 1;j < n;j++){
            if(((i >> j) & 1) && a[p][j]){
                in[i]++;
                dsu[i].merge(p, j);
            }
        }
    }

    //cerr << "OK" << endl;

    int full = (1 << n) - 1;

    i64 ans = 0;
    for(int i = 0;i < len;i++){
        if(popc[i] % 2 == 0){
            ans = (ans + 1ll * power(2, in[full ^ i]) * (dsu[i].calc(i) % P)) % P;
            //cerr << i << " add "<< " " << 1ll * power(2, in[full ^ i]) * (dsu[i].calc(i) % P) << endl;
        }
        else{
            ans = (ans - 1ll * power(2, in[full ^ i]) * (dsu[i].calc(i) % P) % P + P) % P; 
            //cerr << i << " sub "<< " " << 1ll * power(2, in[full ^ i]) * (dsu[i].calc(i) % P) << endl; 
        }
    }
    ans = (ans % P + P)  % P;

    cout << ans << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}