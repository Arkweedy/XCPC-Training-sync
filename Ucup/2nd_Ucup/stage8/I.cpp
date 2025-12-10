#include<bits/stdc++.h>

using namespace std;
#define lowbit(x) ((x)&(-x))
using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 5e5 + 10;

int n,m,a[N],b[N],lst[N],ha[N];
int bit[N];

void add(int x,int t){
    while(x<=n){
        bit[x] += t;
        x += lowbit(x);
    }
}

int query(int x){
    int res = 0;
    while(x){
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}


struct Node{
    int l,r,v;
    bool operator < (const Node &a)const{
        return l<a.l;
    }
};
vector<int>e[N];
vector<pair<int,int>>seg[N];
bool vis[N];
void solve()
{
    cin>>n>>m;
    int cur = 0;
    set<int>s;
    for(int i=1;i<=n;i++){
        seg[i].clear();
        bit[i] = 0;
        cin>>a[i];a[i]--;
        e[a[i]].push_back(i);
        s.insert(a[i]);
        while(s.count(cur))cur++;
        b[i] = cur;
        
    }
    
    set<Node>odt;
    for(int i=1;i<=n;){
        int j = i;
        while(j<= n && b[j] == b[i])j++;
        odt.insert({i,j-1,b[i]});
        i = j;
    }

    for(int i=n;i;i--){
        lst[i] = n + 1;
        if(ha[a[i]])lst[i] = ha[a[i]];
        ha[a[i]] = i;
    }
    vector<array<int,3>>range;
    for(int i=1;i<=n;i++){
        auto it =odt.lower_bound({lst[i],0,0});
        it = prev(it);
        int x = n + 1,y = 0;
        while(it -> v >= a[i]){
            auto [l,r,v] = *it;
            x = min(x,l);
            y = max(r,y);
//            seg[v].push_back({i,l});
            range.push_back({i,l,v});
            if(r >= lst[i])odt.insert({lst[i],r,v});
            
            if(it == odt.begin()){
                odt.erase(it);
                break;
            }
            
            auto nit = prev(it);
            odt.erase(it);
            it = nit;
        }
        
        y = min(y,lst[i]-1);
        if(x<=y){
            odt.insert({x,y,a[i]});
        }
        range.push_back({i,i,(a[i]==0)});
        //seg[a[i]==0].push_back({i,i});
        
        it = odt.begin();
        int r = it->r,v = it->v;
        odt.erase(it);
        if(r>i)odt.insert({i+1,r,v});
    }
    
    for(auto [l,r,v]:range){
        if(e[v].empty()){
            seg[n].push_back({1,v});
            continue;
        }
        if(!vis[v]){
            e[v].push_back(0);
            e[v].push_back(n+1);
            sort(e[v].begin(),e[v].end());
            vis[v] = 1;
        }
        auto y = lower_bound(e[v].begin(),e[v].end(),r) - e[v].begin();
        auto x = upper_bound(e[v].begin(),e[v].end(),l) - e[v].begin() - 1;
        seg[e[v][y]-1].push_back({e[v][x]+1,v});
    }
    
    for(int i=1;i<=n;i++)ha[a[i]] = 0;
    
    int res = -1e9;
    for(int i=1;i<=n;i++){
        add(ha[a[i]]+1,1);
        add(i+1,-1);
        for(auto [j,v]:seg[i]){
            //cout<<j<<' '<<i<<' '<<v<<' '<<query(j)<<' '<<query(j) - v - 1<<endl;
            res = max(res,query(j) - v - 1);
        }
        ha[a[i]] = i;
    }
    cout<<res<<'\n';
    for(int i=1;i<=n;i++)ha[a[i]] = 0,e[a[i]].clear();
    for(auto [l,r,v]:range)vis[v] = 0;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
