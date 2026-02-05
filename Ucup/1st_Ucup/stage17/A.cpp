#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 17:37:54

const int N = 1e6 + 10,mod = 998244353;

int f[N],sz[N],cnt[N],n;
int find(int x){
    if(f[x]!=x)f[x]= find(f[x]);
    return f[x];
}

void merge(int u,int v){
    u = find(u),v = find(v);
    cnt[u]++;
    if(u == v){
        return;
    }
    f[v] = u;
    cnt[u] += cnt[v];
    sz[u] += sz[v];
}

void solve()
{
    cin>>n;
    int m = 2 * n - 2;

    for(int i=1;i<=m;i++){
        f[i] = i;
        sz[i] = 1;
    }

    for(int i=1;i<=m;i++){
        int u,v;cin>>u>>v;
        if(u>v)swap(u,v);
        if(u==v){
            cout<<0<<'\n';
            return;
        }
        // add(2*u-1,i+m,1);
        // add(2*v-2,i+m,1);
        merge(2*u-1,2*v-2);
        
    }

    ll res = 1;
    set<int>s;
    for(int i=1;i<=m;i++){
        s.insert(find(i));
    }

    for(auto u:s){
        if(cnt[u] != sz[u])res *= 0;
        else res = res * 2 % mod;
    }

    cout<<res<<'\n';
    
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}