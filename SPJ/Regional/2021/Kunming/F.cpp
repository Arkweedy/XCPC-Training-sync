#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

using ld = long double;

const int N  =1e5 + 10;

int n,b[N];
ld a[N],res;
vector<int>e[N];
ld dfs(int u,int f){
    ld mx[2] = {0,-1e18};
    for(auto v:e[u]){
        if(v==f)continue;
        ld t = dfs(v,u);
        if(t > mx[0]){
            mx[1] = mx[0];
            mx[0] = t;
        }
        else if(t > mx[1]){
            mx[1] = t;
        }
    }
    res = max(res,mx[0] + mx[1] + a[u]);
    return mx[0] + a[u];
}

bool check(ld k){
    for(int i=1;i<=n;i++)a[i] = b[i] - k;
    res = -1e18;
    dfs(1,0);
    return res >= 0;
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    ld l = -1e5,r = 1e5;
    for(int t=0;t<50;t++){
        ld mid =(l+r)/2;
        if(check(mid))l=mid;
        else r=mid;
    }
    l = (l+r)/2;
    ld ans = l*l/4;

    for(int i=1;i<=n;i++){
        b[i] = -b[i];
    }
    l = -1e5,r = 1e5;
    for(int t=0;t<50;t++){
        ld mid =(l+r)/2;
        if(check(mid))l=mid;
        else r=mid;
    }

    ans = max(ans,l*l/4);

    cout<<fixed<<setprecision(10);
    cout<<ans;
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