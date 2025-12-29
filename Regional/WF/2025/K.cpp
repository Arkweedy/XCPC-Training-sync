#include<bits/stdc++.h>


using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

#define int long long

const int N = 3e5 + 10;

struct Point{
    ll x,y,v;

    bool operator<(const Point &W)const{
        return x < W.x;
    }
}p[N];

int n,m,k,tx,ty,f[N];
ll d[N];

int find(int x){
    if(f[x]!=x){
        int pa = find(f[x]);
        d[x] += d[f[x]];
        f[x] = pa;
    }
    return f[x];
}

vector<Point>e[N];
set<pair<ll,ll>>s[N];

pair<int,int> get(){
    for(int i=1;i<=m;i++)e[i].clear();
    for(int i=1;i<=n;i++){
        f[i] = i,d[i] = 0;
        s[i].clear();
    }
    for(int i=0;i<k;i++){
        auto [x,y,v] = p[i];
        e[y].push_back(p[i]);
    }
    for(int i=1;i<=m;i++){
        sort(e[i].begin(),e[i].end());
        int y = i;
        for(int j=1;j<e[y].size();j++){
            auto [x1,y1,v1] = e[y][j-1];
            auto [x2,y2,v2] = e[y][j];
            int p1 = find(x1),p2 = find(x2);
            if(p1 == p2){
                if(v1 - v2 != d[x1] - d[x2]){
                    return {-1,-1};
                }
                continue;
            }
            f[p1] = p2;
            d[p1] = -d[x1] - v2 + v1 + d[x2];
        }
    }

    for(int i=1;i<=n;i++){
        s[find(i)].insert({d[i],i});
    }

    set<ll>ans;
    ll res = 0;

    for(int i=1;i<=m;i++){
        for(auto [x,y,v]:e[i]){
            int p = find(x);
            s[p].erase({d[x],x});
            if(i == ty){
                int tag = find(tx);
                if(tag == p){
                    ans.insert(v -d[x] + d[tx]);
                }
            }
        }

        for(auto [x,y,v] : e[i]){
            int p = find(x);
            if(s[p].empty())continue;
            auto [dmin, _ ] = (*s[p].begin());
            if(v - d[x] + dmin < 0)return {-1,-1};
        }

        int tp = find(tx);
        if(s[tp].size()){
            auto [dmin, _] = (*s[tp].begin());
            res = max(res, d[tx] - dmin);
        }


        for(auto [x,y,v]:e[i]){
            int p = find(x);
            s[p].insert({d[x],x});
        }
    }

    if(ans.size() > 1)return {-1,-1};
    if(ans.size() == 1){
        ll v = (*ans.begin());
        if(v < res)return {-1,-1};
        return {v,1};
    }
    return {res,0};
}

void solve()
{
    cin>>n>>m>>k>>tx>>ty;
    for(int i=0;i<k;i++){
        cin>>p[i].x>>p[i].y>>p[i].v;
    }
    auto [f1,g1] = get();
    // cout<<f1<<' '<<g1<<endl;
    // return;
    for(int i=0;i<k;i++){
        swap(p[i].x,p[i].y);
    }
    swap(n,m),swap(tx,ty);
    auto [f2,g2] = get();
    if(f1 == -1 || f2 == -1){
        cout<<"impossible\n";
        return;
    }
    if(g1 == 1 || g2 == 1){
        if(g1 == 1 && g2 == 1 && f1 != f2){
            cout<<"impossible\n";
            return;
        }
        if(g1 == 1){
            cout<<f1<<'\n';
            return;
        }
        else {
            cout<<f2<<'\n';
            return;
        }
    }

    cout<<max(f1,f2)<<'\n';
}

signed main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}