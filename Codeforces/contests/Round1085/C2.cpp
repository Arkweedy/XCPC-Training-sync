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

    vector<i64>pa(n);
    for(int i = 0;i < n;i++){
        pa[i] = a[i];
        if(i > 0)pa[i] += pa[i - 1];
    }

    auto get = [&](int l, int r)->i64
    {
        i64 res = pa[r];
        if(l > 0)res -= pa[l];
        return res;
    };

    vector<int>ls(n, -1), rs(n, -1), fa(n, n);
    vector<int>l(n), r(n);
    vector<int>stk;

    auto add_edge = [&](int p, int s)->void
    {
        if(s == -1)return;
        if(p < s){
            rs[p] = s;
            fa[s] = p;
        }
        else{
            ls[p] = s;
            fa[s] = p;
        }
    };

    for(int i = 0;i < n;i++){
        int la = -1;
        while(!stk.empty() && a[i] > a[stk.back()]){
            add_edge(stk.back(), la);
            //rs[stk.back()] = la;
            la = stk.back();
            stk.pop_back();
        }
        stk.push_back(i);
        add_edge(i, la);
        //ls[i] = la;
    }
    while(!stk.size() >= 2){
        int m = stk.size();
        add_edge(stk[m - 2], stk[m - 1]);
        stk.pop_back();
    }
    int rt = stk[0];

    vector<int>dp1(n), dp2(n);
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
        l[p] = r[p] = p;
        if(ls[p] != -1){
            self(self, ls[p]);
            dp1[p] = max(dp1[p], dp1[ls[p]] + (r[p] - p + 1) * (h - a[p]));
            dp2[p] = max(dp2[p], dp2[ls[p]] + (r[p] - p + 1) * (h - a[p]));
        }
        if(rs[p] != -1){
            self(self, rs[p]);
            dp1[p] = max(dp1[p], dp1[rs[p]] + (p - l[p] + 1) * (h - a[p]));
            dp2[p] = max(dp2[p], dp2[rs[p]] + (p - l[p] + 1) * (h - a[p]));
        }
        if(ls[p] != -1 && rs[p] != -1){
            dp2[p] = max(dp2[p], dp1[ls[p]] + dp1[rs[p]] + h - a[p]);
        }
        return;
    };
    dfs2(dfs2, rt);
    i64 ans = min(dp1[rt], dp2[rt]);
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