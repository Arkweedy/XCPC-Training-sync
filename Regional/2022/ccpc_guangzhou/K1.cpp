#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 2e5 + 10;

int n,m;
ll s1,s2,s3,s4;
vector<int> e[N];
int deg[N];

void solve()
{
    s1=s2=s3=0;
    cin>>n>>m;

    for(int i=1;i<=n;i++) e[i].clear(),deg[i]=0;
    for(int i=1;i<=m;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
        deg[u]++;deg[v]++;
    }
    //cal s1
    // vector<int> ve;
    //  int nn=sqrt(max(n,m));
    // for(int i=1;i<=n;i++)
    //     if(deg[i]>=nn)
    //     {
    //         assert(cnt==0);
    //         add(i);
    //         for(auto v:e[i]) add(v);
    //         for(auto v:e[i])
    //         {
    //             if(v<i&&deg[v]>=nn) continue;
    //             for(auto vv:e[v]) add(vv);
    //             s1+=n-cnt;
    //             for(auto vv:e[v]) de(vv);
    //         }
    //         for(auto v:e[i]) de(v);
    //         de(i);
    //     }
    
    // for(int i=1;i<=n;i++)
    // {
    //     for(auto v:e[i])
    //     {
    //         if(v>i) continue;
    //         if(deg[i]<nn&&deg[v]<nn)
    //         {
    //             assert(cnt==0);
    //             cal(i,v);
    //         }
    //     }
    // }
//    cout<<s1<<endl;
    //return ;
    {
        vector<int>id(n+1),rk(n+1);
        for(int i=1;i<=n;i++)id[i] = i;
        sort(id.begin()+1,id.end(),[&](int x,int y){
            return make_pair(deg[x],x) < make_pair(deg[y],y);
        });

        vector<vector<int>>V(n+1);
        for(int i=1;i<=n;i++)rk[id[i]] = i;
        for(int i=1;i<=n;i++){
            for(auto v:e[i]){
                if(rk[v] > rk[i]){
                    V[i].push_back(v);
                }
            }
        }

        vector<int>vis(n+1);
        for(int i=1;i<=n;i++){
            for(auto v:V[i])vis[v] = 1;
            for(auto v1 : V[i]){
                for(auto v2 : V[v1]){
                    if(vis[v2])s3++;
                }
            }
            for(auto v:V[i])vis[v] = 0;
        }

        ll s4 = 0;
        for(int i=1;i<=n;i++){
            for(auto v1 : e[i]){
                for(auto v2 : V[v1]){
                    if(rk[v2] > rk[i])s4 += vis[v2],vis[v2]++;
                }
            }
            for(auto v1:e[i]){
                for(auto v2:V[v1])vis[v2] = 0;
            }
        }

        // cout<<s3<<endl;
        ll m = 0;
        for(int i=1;i<=n;i++){
            m += deg[i];
            s2 += 1ll * deg[i] * (deg[i]-1)/2;
        }
        s2 -= 3 * s3;
        m/=2;
        ll res = 1ll *m * (n+m-3) + s2 + 6*s3 + s4;
        cout<<res % (1000000007)<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}