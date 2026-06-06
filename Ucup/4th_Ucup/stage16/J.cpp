#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n,k,m;cin>>n>>k>>m;
    vector<vector<pair<int,int>>>e(k);
    for(int i=0;i<k;i++){
        int x;cin>>x;
        while(x--){
            int a,b;cin>>a>>b;
            e[i].push_back({a,b+1});
        }
    }
    vector<int>c;
    for(int i=0;i<k;i++){
        for(auto [l,r]:e[i])c.push_back(l),c.push_back(r);
    }
    sort(c.begin(),c.end());
    c.erase(unique(c.begin(),c.end()),c.end());

    vector<ll>f(1<<k);
    vector<vector<int>>ne(c.size());

    for(int i=0;i<k;i++){
        for(auto [l,r]:e[i]){
            l = lower_bound(c.begin(),c.end(),l) - c.begin();
            r = lower_bound(c.begin(),c.end(),r) - c.begin();
            for(int j=l;j<r;j++)ne[j].push_back(i);
        }
    }

    for(int i=0;i+1<c.size();i++){
        ll val = c[i+1] - c[i];
        int mask = 0;
        for(auto x:ne[i])mask |= 1 << x;
        mask = ((1<<k)-1) ^ mask;
        f[mask] -= (ne[i].size() - 1) * val;
        for(auto x:ne[i])f[mask | (1 << x)] += val;
    }

    for(int i=0;i<k;i++){
        for(int j=0;j<(1<<k);j++){
            if(j>>i&1)continue;
            f[j] += f[j^(1<<i)];
        }
    }

    int res = 0;
    for(int i=0;i<(1<<k);i++){
        if(f[i] <= c.back() - c[0] - m)res++;
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
    return 0;
}