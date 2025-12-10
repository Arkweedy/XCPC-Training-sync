#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, q, k;
    cin>>n>>q>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<pair<int,int>>qry;
    qry.reserve(q);
    for(int i = 0;i < q;i++){
        int x,y;
        cin>>x>>y;
        x--,y--;
        qry.emplace_back(x,y);
    }

    vector<int>ans(q);
    vector<int>pl(n + 1),pr(n + 1);
    for(int i = 1;i * i <= k;i++){
        int l = i, r = k / (i + 1);
        // [1,l] (r, inf)
        // if alloc in for -> sqrt(k) * n times alloc (1e3 * n / 4)
        for(int i = 0;i < n;i++){
            pl[i + 1] = pl[i] + (a[i] <= l);
            pr[i + 1] = pr[i] + (a[i] > r);
        }
        for(int i = 0;i < q;i++){
            auto& [x, y] = qry[i];
            int lc = pl[y + 1] - pl[x], rc = pr[y + 1] - pr[x];
            if(lc + rc == y - x + 1 && (y - x + 1) % 2 == 1){
                ans[i] = max(ans[i], (rc - lc) / 2);
            }
            else{
                ans[i] = max(ans[i], (rc - lc + 1) / 2);
            }
        }
    }
    

    for(int i = 0;i < q;i++){
        cout<<ans[i]<<" ";
    }
    cout<<"\n";
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