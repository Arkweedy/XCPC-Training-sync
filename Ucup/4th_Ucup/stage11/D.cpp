#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.20 13:29:42

struct DSU{
    int n;
    vector<int>f,sz,e,loop;

    DSU(int _n)
    {
        n = _n;
        f.resize(n);
        iota(f.begin(),f.end(), 0);
        sz.resize(n, 1);
        e.resize(n, 0);
        loop.resize(n);
    }

    int find(int p)
    {
        return p == f[p] ? p : (f[p] = find(f[p]));
    }

    void merge(int u, int v)
    {
        if(u == v){
            e[find(u)]++;
            loop[find(u)] = 1;
            return;
        }
        u = find(u);
        v = find(v);
        if(u == v){
            e[u]++;
            return;
        }
        if(sz[u] < sz[v])swap(u, v);
        f[v] = u;
        sz[u] += sz[v];
        e[u] += e[v] + 1;
        loop[u] = (loop[u] | loop[v]);
        return;
    } 
};

constexpr int P = 1e9 + 7;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>>p(n, make_pair(-1,-1));
    int flg = 0;
    for(int i = 0;i < m;i++){
        int x, a, b;
        cin >> a >> b >> x;
        x--;
        a--;
        b--;
        if(p[x] == make_pair(-1,-1)){
            p[x] = make_pair(a, b);

        }
        else{
            pair<int,int>np = {-1,-1};
            auto [c, d] = p[x];
            if(a == c || a == d){
                np.first = a;
            }
            if(b == c || b == d){
                np.second = b;
            }
            p[x] = np;
            if(p[x] == make_pair(-1,-1)){
                flg = 1;
            }
        }
    }

    if(flg){
        cout << 0 << endl;
        return;
    }

    int free = 0;
    DSU dsu(n);
    for(int i = 0;i < n;i++){
        auto [x, y] = p[i];
        //cerr << x + 1 << " " << y + 1 << endl;
        if(x == -1 && y == -1){
            free++;
        }
        else if(x == -1 || y == -1){
            int v = max(x, y);
            dsu.merge(v, v);
        }
        else{
            dsu.merge(x, y);
        }
    }

    int ans = 1;
    for(int i = 2;i <= free;i++){
        ans = 1ll * ans * i % P;
    }
    for(int i = 0;i < n;i++){
        //cerr << ans << endl;
        if(dsu.find(i) == i){
            if(dsu.e[i] == dsu.sz[i] - 1){
                ans = 1ll * ans * dsu.sz[i] % P;
            }
            else if(dsu.e[i] == dsu.sz[i]){
                if(!dsu.loop[i]){
                    ans = 1ll * ans * 2 % P;
                }
            }
            else{
                ans = 0;
            }
        }
    }

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