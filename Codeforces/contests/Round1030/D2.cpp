#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,k;
    cin>>n>>k;
    vector<ll>p(n),d(n);
    for(int i = 0;i < n;i++){
        cin>>p[i];
    }
    for(int i = 0;i < n;i++){
        cin>>d[i];
    }
    int q;
    cin>>q;
    vector<ll>qry(q);
    for(int i = 0;i < q;i++){
        cin>>qry[i];
    }
    map<ll,vector<int>>lmp,rmp;// l => r, r => l
    map<ll,vector<ll>>lpos;
    for(int i = 0;i < n;i++){
        ll x = ((p[i] - d[i]) % k + k) % k;
        lmp[x].push_back(i);
        lpos[x].push_back(p[i]);
    }
    for(int i = 0;i < n;i++){
        ll y = (p[i] + d[i]) % k;
        rmp[y].push_back(i);
    }
    vector<int>g(n * 2 + 2);//l->r, r->l, lend, rend
    vector<vector<int>>rg(n * 2 + 2);
    int lend = n * 2, rend = n * 2 + 1;
    for(const auto &[x, vec] : lmp){
        for(int i = 0;i + 1 < vec.size();i++){
            g[vec[i]] = vec[i + 1] + n;
            rg[vec[i + 1] + n].push_back(vec[i]);
        }
        g[vec[vec.size() - 1]] = rend;
        rg[rend].push_back(vec[vec.size() - 1]);
    }
    for(const auto &[x, vec] : rmp){
        for(int i = vec.size() - 1;i > 0;i--){
            g[vec[i] + n] = vec[i - 1];
            rg[vec[i - 1]].push_back(vec[i] + n);
        }
        g[vec[vec.size() - 1] + n] = lend;
        rg[lend].push_back(vec[0] + n);
    }

    vector<int>ok(n * 2 + 2, 0);
    vector<int>vs(n * 2 + 2);
    auto dfs = [&](auto&&self, int p)->void
    {
        ok[p] = 1;
        for(auto s : rg[p]){
            self(self, s);
        }
        return;
    };
    
    dfs(dfs,lend);
    dfs(dfs,rend);
    
    for(int i = 0;i < q;i++){
        ll a = qry[i];
        if(!lmp.count(a % k)){
            cout<<"YES"<<endl;
        }else{
            const auto& vec = lmp[a % k];
            const auto&pvec = lpos[a % k];
            int p = lower_bound(pvec.begin(),pvec.end(),a) - pvec.begin();
            if(p == pvec.size()){
                cout<<"YES"<<endl;
            }else{
                if(ok[vec[p] + n]){
                    cout<<"YES"<<endl;
                }else{
                    cout<<"NO"<<endl;
                }
            }
        }
    }
    return;
}

signed main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}