#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    m *= 2;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
        a[i] *= 2;
    }
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    //shuffle(a.begin(),a.end(),g);
    sort(a.begin(),a.end(),greater<>());
    auto sa = a;
    for(int i = n - 1;i > 0;i--){
        sa[i - 1] += sa[i];
    }
    int res = 0;
    map<ll,int>mp;
    auto dfs1 = [&](auto&&self,int p, ll val, int cut)->void
    {
        //res ++ ;
        if(!mp.count(val))mp[val] = cut;
        else if(mp[val] >= cut)mp[val] = cut;

        if(val + sa[p] < m)return;
        if(val > m)return;

        if(p >= n / 2)return;
        self(self, p + 1, val, cut);
        self(self, p + 1, val +  a[p], cut);
        self(self, p + 1, val + a[p] / 2, cut + 1);
    };

    dfs1(dfs1,0,0,0);
    int ans = 114514;
    auto dfs2 = [&](auto&&self,int p, ll val, int cut)->void
    {
        // res ++ ;
        // if(res > 2e7)return;
        if(mp.count(m - val))ans = min(ans, mp[m - val] + cut);
        if(p == n)return;
        self(self, p + 1, val, cut);
        self(self, p + 1, val + a[p], cut);
        self(self, p + 1, val + a[p] / 2, cut + 1);
    };
    dfs2(dfs2,n / 2, 0,0);
    if(ans == 114514)cout<<-1<<endl;
    else cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}