#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

int f[N],n,m,a[N];

vector<int>e[N];
int find(int x){
    if(f[x]!=x){
        int p = find(f[x]);
        a[x] ^= a[f[x]];
        f[x] = p; 
    }
    return f[x];
}

void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)f[i] = i;
    while(m--){
        int u,v,w;cin>>u>>v>>w;
        if(find(u) == find(v)){
            if((a[u]^a[v])!=w){
                cout<<"-1\n";
                return;
            }
        }
        int pu = find(u),pv = find(v);
        f[pv] = pu;
        a[pv] = a[v] ^ w ^ a[u];
    }

    for(int i=1;i<=n;i++)e[find(i)].push_back(i);

    ll res = 0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<30;j++){
            int cnt[2] = {0};
            for(auto u:e[i]){
                find(u);
                cnt[a[u]>>j&1]++;
            }
            res += (1ll << j) * min(cnt[0],cnt[1]);
        }
    }

    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
}