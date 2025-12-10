#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, k;
    cin>>n>>k;
    vector<int>p(n);
    for(int i = 0;i < n;i++){
        cin>>p[i];
        p[i]--;
    }
    vector<int>pi(n);
    for(int i = 0;i < n;i++){
        pi[p[i]] = i;
    }

    vector<vector<int>>cnt(n,vector<int>(n));
    //cnt[i][j] -> haven in pi_1 ~ pi_i , in j
    for(int i = 0;i < n;i++){
        if(pi[i] > 0)cnt[i][pi[i] - 1] = 1;
    }
    for(int i = 0;i < n;i++){
        for(int j = n - 1;j > 0;j--){
            cnt[i][j - 1] += cnt[i][j];
        }
    }
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < n;j++){
            cnt[i + 1][j] += cnt[i][j];
        }
    }

    auto get_pre = [&](int i, int v)->int
    {
        if(i == -1)return 0;
        return cnt[i][v];
    };

    auto get_mask = [&](int l, int mask, int v)->int
    {
        int res = 0;
        for(int i = 0;i < k;i++){
            if(mask >> i & 1){
                res += v < pi[l + i + 1] ? 1 : 0;
            }
        }
        return res;
    };

    int len = 1 << k;
    constexpr int inf = 1e9;
    vector<vector<int>>dist(n + 2, vector<int>(len, inf));
    vector<pair<int,int>>dp;//l, mask
    dp.push_back({0,0});
    dist[0][0] = 0;

    for(int i = 0;i < n;i++){
        vector<pair<int,int>>ndp;
        for(auto [l, mask] : dp){
            if(dist[l][mask] == -1)continue;
            int d = dist[l][mask];
            dist[l][mask] = -1;
            //insert mask 0
            for(int j = 0;j < k && l + j + 1 < n;j++){
                if(!(mask >> j & 1)){
                    int nmask = mask ^ (1 << j);
                    dist[l][nmask] = min(dist[l][nmask], d + get_pre(l - 1, pi[l + j + 1]) + get_mask(l, mask, pi[l + j + 1]));
                    ndp.emplace_back(l,nmask);
                }
            }
            //insert l
            int p = 0;
            while(mask >> p & 1)p++;
            int nl = l + p + 1, nmask = mask >> p + 1;
            dist[nl][nmask] = min(dist[nl][nmask], d + get_pre(l - 1, pi[l]) + get_mask(l, mask, pi[l]));
            ndp.emplace_back(nl,nmask);
        }
        dp = move(ndp);
    }

    int ans = dist[n][0];
    cout<<ans<<endl;
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