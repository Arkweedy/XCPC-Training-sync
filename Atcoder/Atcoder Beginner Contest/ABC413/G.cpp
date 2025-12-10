#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
    vector<int>lx,rx;
    vector<int>ly,ry;

public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
        lx.resize(n);
        rx.resize(n);
        ly.resize(n);
        ry.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    void init(int x, int y, int p)
    {
        lx[p] = rx[p] = x;
        ly[p] = ry[p] = y;
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    int size(int p)
    {
        return sz[find(p)];
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            scc--;
            sz[fu] += sz[fv];
            fa[fv] = fu;
            lx[fu] = min(lx[fu],lx[fv]);
            rx[fu] = max(rx[fu],rx[fv]);
            ly[fu] = min(ly[fu],ly[fv]);
            ry[fu] = max(ry[fu],ry[fv]);
            return true;
        }
    }

    int get_lx(int p)
    {
        return lx[find(p)];
    }

    int get_rx(int p)
    {
        return rx[find(p)];
    }

    int get_ly(int p)
    {
        return ly[find(p)];
    }

    int get_ry(int p)
    {
        return ry[find(p)];
    }
};


void solve()
{
    int n, m, k;
    cin>>n>>m>>k;
    vector<int>x(k),y(k);
    for(int i = 0;i < k;i++){
        cin>>x[i]>>y[i];
        x[i]--,y[i]--;
    }
    DSU dsu(k);
    map<pair<int,int>,int>mp;
    int tot = 0;
    int dx[8] = {1,1,1,0,0,-1,-1,-1}, dy[8] = {0,1,-1,1,-1,1,-1,0};
    auto ok = [&](int x, int y)->bool
    {
        return x >= 0 && x < n && y >= 0 && y < m;
    };
    for(int i = 0; i < k;i++){
        pair<int,int>p = make_pair(x[i],y[i]);
        if(!mp.count(p)){
            mp[p] = tot++;
            dsu.init(x[i],y[i],mp[p]);
        }
        for(int j = 0;j < 8;j++){
            int nx = x[i] + dx[j], ny = y[i] + dy[j];
            if(ok(nx,ny)){
                pair<int,int>pr =make_pair(nx,ny);
                if(mp.count(pr))dsu.merge(mp[pr],mp[p]);
            }
        }
    }

    for(int i = 0;i < k;i++){
        if((dsu.get_lx(i) == 0 && dsu.get_rx(i) == n - 1) || (dsu.get_ly(i) == 0 && dsu.get_ry(i) == m - 1)){
            cout<<"No"<<endl;
            return;
        }
        else if((dsu.get_lx(i) == 0 && dsu.get_ly(i) == 0) || (dsu.get_rx(i) == n - 1 && dsu.get_ry(i) == m - 1)){
            cout<<"No"<<endl;
            return;
        }
    }
    cout<<"Yes"<<endl;
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