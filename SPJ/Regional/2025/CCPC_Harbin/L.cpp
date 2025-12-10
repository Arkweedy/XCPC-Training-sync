#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 1e9 + 7;

void solve()
{
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<int>pos(m, -1);
    vector<int>rk(m, -1);
    for(int i = 0;i < k;i++){
        int r,c;
        cin >> r >> c;
        c--;
        r--;
        pos[c] = r;
        rk[c] = i;
    }

    constexpr int inf = 1e9;
    vector<int>ans(1 << k);

    auto upt = [&](vector<int>&dp, int l, int r)->void
    {
        for(int i = l + 1;i <= r;i++){
            dp[i] = min(dp[i], dp[i - 1] + 1);
        } 
        for(int i = r - 1;i >= l;i--){
            dp[i] = min(dp[i], dp[i + 1] + 1);
        }
        return;
    };

    auto dfs = [&](auto&&self, int c, vector<int>dp, int mask)->void
    {
        if(c == m){
            int res = inf;
            for(int i = 0;i < n;i++){
                res = min(res, dp[i]);
            }
            if(res == inf)ans[mask] = -1;
            else ans[mask] = res;
            return;
        }
        if(pos[c] == -1){
            for(int i = 0;i < n;i++){
                dp[i]++;
            }
            upt(dp, 0, n - 1);
            self(self, c + 1, dp, mask);
        }
        else{
            // 0, up
            {
                vector<int>ndp(n);
                int p = pos[c];
                for(int i = 0;i < p;i++){
                    ndp[i] = dp[i] + 1;
                    if(pos[c - 1] != p - 1)ndp[i] = min(ndp[i],dp[p] + p - i + 1);
                }
                upt(ndp, 0, p - 1);
                for(int i = p;i < n;i++){
                    ndp[i] = inf;
                }
                self(self, c + 1, ndp, mask);
            }
            {
                vector<int>ndp(n);
                int p = pos[c];
                for(int i = p + 1;i < n;i++){
                    ndp[i] =dp[i] + 1;
                    if(pos[c - 1] != p + 1)ndp[i] = min(ndp[i], dp[p] + i - p + 1);
                }
                upt(ndp, p + 1, n - 1);
                for(int i = 0;i <= p;i++){
                    ndp[i] = inf;
                }
                self(self, c + 1, ndp, mask | (1 << rk[c]));
            }
            return;
        }
    };
    dfs(dfs, 1, vector<int>(n,0), 0);

    for(int i = 0;i < (1 << k);i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}