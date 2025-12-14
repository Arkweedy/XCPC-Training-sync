#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

class Dsu{
public:
    int n;
    vector<int>f;
    vector<int>sz;
    
    Dsu(int n_)
    {
        n = n_;
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
        if(sz[u] < sz[u])swap(u,v);
        sz[u] += sz[v];
        f[v] = u;
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
    
    vector<int>a,cnt;
    for(auto [val, c] : mp){
        a.push_back(val);
        cnt.push_back(c);
    }
    
    int m = a.size();
    vector<pair<int,int>>e;
    for(int i = 0;i < m;i++){
        int p = lower_bound(a.begin(),a.end(), k - a[i]) - a.begin();
        for(int j = 0;j < min(10,m);j++){
            e.emplace_back(i, (p + j) % m);
        }
    }
    
    auto dis = [&](int u, int v)->int
    {
        return (a[u] + a[v]) >= k ? (a[u] + a[v] - k) : (a[u] + a[v]);
    };
    
    sort(e.begin(),e.end(), [&](pair<int,int>&i , pair<int,int>&j)->bool
    {
        return dis(i.first,i.second) < dis(j.first,j.second);
    });

    vector<int>ismerge(m);
    Dsu dsu(m);
    
    ll ans = 0;
    
    for(auto [u,v] : e)
    {
        if(u == v){
            if(ismerge[u])continue;
            else{
                ans += 1ll * (cnt[u] - 1) * dis(u,v);
                ismerge[u] = 1;
            }
        }
        else{
            if(!dsu.same(u, v)){
                
                if(!ismerge[u] && !ismerge[v]){
                    ans += 1ll * (cnt[u] + cnt[v] - 1) * dis(u,v);
                }
                else if(!ismerge[u] || !ismerge[v]){
                    if(ismerge[u])swap(u,v);
                    ans += 1ll * cnt[u] * dis(u,v);
                }
                else{
                    ans += dis(u,v);
                }
                dsu.merge(u,v);
                ismerge[u] = ismerge[v] = 1;
            }
        }
    }
    
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
