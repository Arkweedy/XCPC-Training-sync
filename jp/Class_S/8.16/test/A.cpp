#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using namespace std;
const int N=16005;
#define int long long
int n,dp[N];
vector<int> a(N+1);
vector<int> g[N+5];
void dfs(int p,int x){
    dp[p]=a[p];
    for(auto i:g[p]){
        if(i!=x){
            dfs(i,p);
            if(dp[i]>=0) dp[p]+=dp[i];
        }
    }
}
signed main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    int ans=INT_MIN;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans;
    return 0;
}