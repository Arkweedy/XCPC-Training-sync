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
    vector<int>lsz(n + 1), rsz(n + 1);
    vector<int>fa(n + 1);

    auto build = [&](auto&&self, int l, int r)->int
    {
        if(l > r)return 0;
        else if(l == r)return l;
        int m = l + r >> 1;
        lsz[m] = m - l;
        rsz[m] = r - m;
        fa[self(self, l, m - 1)] = fa[self(self, m + 1, r)] = m;
        return m;
    };

    build(build, 1, n);

    unordered_map<int,int>mp;
    vector<i64>ans(n + 1);

    for(int i = 1;i <= n;i++){
        for(auto [k, c] : mp){
            ans[k + lsz[i] + 2] += c;
        }
        mp[rsz[i]]++;
        for(int j = fa[i];j != 0;j = fa[j]){
            if(j > i)ans[lsz[j] + rsz[i] + 2]--;
            else ans[rsz[j] + lsz[i] + 2]--;
            ans[abs(j - i)]++;
        }
    }
    for(int i = n;i >= 0;i--){
        cout << ans[i] << " ";
    }
    //cout << endl;
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