#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.08.16 09:53

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

struct DSU{
    int n;
    vector<int>fa,sz;

    DSU(int n_)
    {
        n = n_;
        fa.resize(n);
        iota(fa.begin(),fa.end(), 0);
        sz.resize(n, 1);
    }

    int find(int p)
    {
        //cerr << p << endl;
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    int merge(int u, int v)
    {
        
        int fu = find(u), fv = find(v);
        //cerr << "merge " << u << " " << v << " " << fu << " " << fv << endl;
        if(fu == fv){
            return 0;
        }
        if(sz[fu] < sz[fv]){
            swap(fu, fv);
        }
        fa[fv] = fu;
        sz[fu] += sz[fv];
        return 1;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;

    DSU dsu(k * 2);
    map<int,int>mpx, mpy;
    int totx = 0, toty = 0;
    int c = 0;
    for(int i = 0;i < k;i++){
        int x, y;
        cin >> x >> y;
        if(!mpx.count(x))mpx[x] = totx++;        
        if(!mpy.count(y))mpy[y] = toty++;
        x = mpx[x];
        y = mpy[y];
        if(dsu.merge(x, y + k))c += 2;
        else c++;
    }
    //cerr << c << " " << n * m << endl;
    i64 cnt = (1ll * n * m - c) % (P - 1);
    int ans = power(2, cnt);
    cout << ans << endl;
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