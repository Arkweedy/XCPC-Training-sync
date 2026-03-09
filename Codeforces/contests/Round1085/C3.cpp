#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.09 16:26:44

void solve()
{
    int n, h;
    cin >> n >> h;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    vector<int>ls(n, -1), rs(n, -1);
    vector<int>l(n), r(n);
    vector<int>stk;
    
    int rt = -1;
    for(int i = 0;i < n;i++){
        int la = -1;
        while(!stk.empty() && a[i] >= a[stk.back()]){
            la = stk.back();
            stk.pop_back();
        }
        ls[i] = la;
        if(!stk.empty()){
            rs[stk.back()] = i;
        }
        stk.push_back(i);
    }
    rt = stk[0];
    stk.clear();

    vector<i64>dp1(n), dp2(n);
    auto dfs1 = [&](auto&&self, int p)->void
    {
        l[p] = r[p] = p;
        if(ls[p] != -1){
            self(self, ls[p]);
            l[p] = min(l[p], l[ls[p]]);
        }
        if(rs[p] != -1){
            self(self, rs[p]);
            r[p] = max(r[p], r[rs[p]]);
        }
        return;
    };
    dfs1(dfs1, rt);

    auto dfs2 = [&](auto&&self, int p)->void
    {
        dp1[p] = dp2[p] = (r[p] - l[p] + 1) * (h - a[p]);
        if(ls[p] != -1){
            self(self, ls[p]);
            dp1[p] = max(dp1[p], dp1[ls[p]] + 1ll * (r[p] - p + 1) * (h - a[p]));
            dp2[p] = max(dp2[p], dp2[ls[p]] + 1ll * (r[p] - p + 1) * (h - a[p]));
        }
        if(rs[p] != -1){
            self(self, rs[p]);
            dp1[p] = max(dp1[p], dp1[rs[p]] + 1ll * (p - l[p] + 1) * (h - a[p]));
            dp2[p] = max(dp2[p], dp2[rs[p]] + 1ll * (p - l[p] + 1) * (h - a[p]));
        }
        if(ls[p] != -1 && rs[p] != -1){
            dp2[p] = max(dp2[p], dp1[ls[p]] + dp1[rs[p]] + h - a[p]);
        }
        return;
    };
    dfs2(dfs2, rt);
    i64 ans = max(dp1[rt], dp2[rt]);
    cout << ans << endl;
    return;
}

int main()
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