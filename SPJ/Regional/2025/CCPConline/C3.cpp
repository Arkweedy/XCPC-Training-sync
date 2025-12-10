#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

class Dsu{
public:
    int n;
    vector<int>f;
    vector<int>sz;
    int scc;
    
    Dsu(int n_)
    {
        n = n_;
        scc = n;
        f.resize(n);
        iota(f.begin(),f.end(),0);
        sz.resize(n, 1);
    }

    int find(int x){
        if(f[x]!=x)f[x] = find(f[x]);
        return f[x];
    }
    
    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    void merge(int u,int v){
        u = find(u), v = find(v);
        if(u==v)return;
        if(sz[u] < sz[v])swap(u,v);
        sz[u] += sz[v];
        f[v] = u;
        scc--;
    }
};

void solve()
{
    int n, k;
    cin>>n>>k;
    map<int,int>mp;
    for(int i = 0;i < n;i++){
        int e;
        cin>>e;
        e %= k;
        mp[e]++;
    }
    
    vector<ll>a,cnt;
    for(auto [val, c] : mp){
        a.push_back(val);
        cnt.push_back(c);
    }
    
    int m = a.size();
    vector<pair<int,int>>e;
    for(int i = 0;i < m;i++){
        int p = lower_bound(a.begin(),a.end(), k - a[i]) - a.begin();
        for(int j = 0;j < min(30,m);j++){
            e.emplace_back(i, (p + j) % m);
        }
        e.emplace_back(i, 0);
    }
    
    auto dis = [&](int u, int v)->ll
    {
        return (a[u] + a[v]) >= k ? (a[u] + a[v] - k) : (a[u] + a[v]);
    };
    
    sort(e.begin(),e.end(), [&](pair<int,int>&i , pair<int,int>&j)->bool
    {
        return dis(i.first,i.second) < dis(j.first,j.second);
    });

    Dsu dsu(m);
    
    ll ans = 0;
    
    for(auto [u,v] : e)
    {
        if(u == v){
            ans += 1ll * (cnt[u] - 1) * dis(u,v);
            cnt[u] = 1;
        }
        else{
            if(!dsu.same(u, v)){
                ans += 1ll * (cnt[u] + cnt[v] - 1) * dis(u,v);
                dsu.merge(u,v);
                cnt[u] = cnt[v] = 1;
            }
        }
    }

    assert(dsu.scc == 1);
    
    cout<<ans<<"\n";
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
