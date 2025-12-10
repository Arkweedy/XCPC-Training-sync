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
    

public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
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
            return true;
        }
    }
};


void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin>>x[i]>>y[i];
    }
    DSU dsu(n + q);
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>>pq;
    for(int i= 0;i < n;i++){
        for(int j = i + 1;j < n;j++){
            int dis = abs(x[i]-x[j]) + abs(y[i] - y[j]);
            pq.push({dis,i,j});
        }
    }
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int a,b;
            cin>>a>>b;
            x.push_back(a);
            y.push_back(b);
            for(int i = 0;i < n;i++){
                int dis = abs(a-x[i]) + abs(b-y[i]);
                pq.push({dis,n,i});
            }
            n++;
        }else if(op == 2){
            int ok = 0;
            int dis = -1;
            while(!pq.empty()){
                auto [d,u,v] = pq.top();
                pq.pop();
                if(dsu.merge(u,v)){
                    ok = 1;
                    dis = d;
                    cerr<<"merge "<<u<<" "<<v<<endl;
                }
                if(ok)break;
            }
            if(ok){
                while(!pq.empty()){
                    auto [d,u,v] = pq.top();
                    if(d != dis)break;
                    pq.pop();
                    dsu.merge(u,v);
                }
                cout<<dis<<endl;
            }else{
                cout<<-1<<endl;
            }
        }else{
            int u,v;
            cin>>u>>v;
            u--,v--;
            if(dsu.same(u,v)){
                cout<<"Yes"<<endl;
            }else{
                cout<<"No"<<endl;
            }
        }
    }
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