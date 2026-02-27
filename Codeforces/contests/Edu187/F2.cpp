#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F2.cpp Create time : 2026.02.27 16:44

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    // n -> n-1/2 -> ...
    vector<pair<int,int>>v;
    vector<int>cnt(n + 1);
    int l = n, r = n;
    int lc = 1, rc = 0;
    v.emplace_back(n, 1);
    cnt[n] = 1;
    while(l != 0){
        int a = (l - 1) / 2, b = l / 2;
        int c = (r - 1) / 2, d = r / 2;
        l = a, r = d;
        if(l == r){
            lc = lc + rc;
            rc = 0;
            v.emplace_back(l, lc);
            cnt[l] = lc;
        }
        else{
            int nlc = lc, nrc = rc;
            if(b == l)nlc += lc;
            else nrc += lc;
            if(c == l)nlc += rc;
            else nrc += rc;
            lc = nlc;
            rc = nrc;
            v.emplace_back(l, lc);
            v.emplace_back(r, rc);
            cnt[l] = lc;
            cnt[r] = rc;
        }
    }
    reverse(v.begin(),v.end());
    assert(v[0].first == 1);

    vector<int>ans(n + 1);
    map<int,map<int,int>>mp;
    mp[1][1] = 1;

    auto merge = [&](map<int,int>& a, map<int,int>& b)->map<int, int>
    {

    };

    for(int i = 1;i < v.size();i++){
        auto [k, c] = v[i];
        int l = (k - 1) / 2, r = k / 2;
        // for(l) for(r) ?
        for(auto [x, c1] : mp[l]){
            for(auto [y, c2] : mp[r]){
                ans[x + y] = (ans[x + y] + 1ll * c1 * c2) % P;
            }
        }
        mp[k] = merge(mp[l], mp[r]);
    }
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