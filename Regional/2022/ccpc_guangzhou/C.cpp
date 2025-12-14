#include<bits/stdc++.h>
using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;


void solve()
{
    int n,m;cin>>n>>m;
    vector<int>x(n+1,1);
    vector<vector<int>>e(n+1),ne(n+1);

    while(m--){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        ne[v].push_back(u);
    }

    vector<ll>dp(n+1,1);
    priority_queue<pair<ll,ll>>heap;
    queue<int>q;
    heap.push({1,n});

    dp[n] = 0;
    while(!heap.empty()){

        auto [cur , u] = heap.top();
        heap.pop();
        cout<<cur<<' '<<u<<endl;
        if(cur <= dp[u])continue;

        dp[u] = cur;

        for(auto v:e[u]){
            if(dp[u] - x[u] > dp[v]){
                x[v] += dp[u] - x[u] - dp[v];
                heap.push({dp[u] - x[u],v});
            }
        }
        
        for(auto v:ne[u]){
            //cout<<x[v] + dp[u]<<endl;
            if(x[v] + dp[u] > dp[v]){
                if(v == 5 && u==8)cout<<dp[u] + x[v]<<"#\n";
                heap.push({x[v] + dp[u],v});
            }
        }

        
        //cout<<u<<' '<<dp[u]<<endl;
    }

    for(int i=1;i<=n;i++)cout<<x[i]<<" \n"[i==n];

    vector<int>deg(n+1);

    for(int i=1;i<=n;i++){
        for(auto v:e[i]){
            deg[i]++;
        }
    }

    q.push(n);

    vector<ll>L(n+1),R(n+1);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v:ne[u]){
            deg[v]--;
            if(deg[v] == 0)q.push(v);
        }
        if(!e[u].empty()){
            L[u] = 1e18; 
            for(auto v:e[u]){
                L[u] = min(L[u],L[v]);
                R[u] = max(R[u],R[v]);
            }
            L[u] += x[u],R[u] += x[u];
        }else{
            L[u] = x[u],R[u] = x[u];
        }
    }

    if(L[1] != R[1]){
        cout<<"No\n";
    }else{
        cout<<"Yes\n";
        for(int i=1;i<=n;i++)cout<<x[i]<<" \n"[i==n];
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