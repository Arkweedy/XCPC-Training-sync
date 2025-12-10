#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    string s;
    cin>>s;
    int n = s.length();

    // === Module A: blogger-style hash + LCP/LCS (0-based wrapper) ===
    const int MOD = 998244353;
    const int BASE = 29;

    // 1-based 前缀哈希：h[0]=0, h[i] = s[1..i] 的哈希；p[i] = BASE^i
    vector<int> p1(n+1), h1(n+1);
    p1[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p1[i] = (long long)p1[i-1] * BASE % MOD;
        int ch = (int)(s[i-1] - 'a' + 1);     // 注意：只取 s[0..n-1]，不含哨兵
        h1[i] = ((long long)h1[i-1] * BASE + ch) % MOD;
    }
    // 1-based 子串哈希：区间 [L..R]（1<=L<=R<=n）
    auto get1 = [&](int L, int R)->int {
        long long val = (h1[R] - (long long)h1[L-1] * p1[R-L+1]) % MOD;
        if (val < 0) val += MOD;
        return (int)val;
    };

    // 与你现有签名一致：lcp(x,y) = 以 x,y 为起点的最长公共前缀长度（0-based）
    // 等价于比较 1-based 的 [x+1..x+len] 与 [y+1..y+len]
    auto lcp = [&](int x, int y)->int {
        int lo = 0, hi = min(n - x, n - y);
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (get1(x + 1, x + mid) == get1(y + 1, y + mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    };

    // 与你现有签名一致：lcs(x,y) = 以 x,y 为“右端点(含)”的最长公共后缀长度（0-based）
    auto lcs = [&](int x, int y)->int {
        if (x < 0 || y < 0) return 0;
        int lo = 0, hi = min(x + 1, y + 1);
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            // [x-mid+1 .. x] 与 [y-mid+1 .. y]
            if (get1(x - mid + 1 + 1, x + 1) == get1(y - mid + 1 + 1, y + 1)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    };
    // === end Module A ===

    auto get_lyndon_suffix = [&](bool order)->vector<int>
    {
        vector<int>lyn(n);
        stack<int>stk;
        for(int i = n - 1;i >= 0;i--){
            lyn[i] = i;
            while(!stk.empty()){
                int j = stk.top();
                int len = lcp(i, j);
                if(order == 0){
                    if(s[i + len] > s[j + len]){//no
                        lyn[i] = j - 1;
                        break;
                    }
                    else{
                        lyn[i] = lyn[j];
                        stk.pop();
                    }
                }
                else{
                    if(s[i + len] < s[j + len]){//no
                        lyn[i] = j - 1;
                        break;
                    }
                    else{
                        lyn[i] = lyn[j];
                        stk.pop();
                    }
                }
            }
            //if(stk.empty())lyn[i] = n - 1;
            stk.push(i);
        }
        return lyn;
    };

    auto lyn0 = get_lyndon_suffix(0);
    auto lyn1 = get_lyndon_suffix(1);

    // for(int i = 0;i < n;i++){
    //     cerr<<lyn0[i]<<" ";
    // }
    // cerr<<endl;
    // for(int i = 0;i < n;i++){
    //     cerr<<lyn1[i]<<" ";
    // }
    // cerr<<endl;


    vector<array<int,3>>runs;
    for(int i = 0;i < n;i++){
        int j,l,r,p;
        j = lyn0[i];//period is j - i + 1, compare i, j + 1 ([i,j] is cyc)
        l = i - 1 - lcs(i - 1, j) + 1, r = j + 1 + lcp(i, j + 1) - 1,p = j - i + 1;
        if(r - l + 1 >= 2 * (j - i + 1)){
            runs.push_back({l, r, p});
            //runs.push_back({l,r,j - i + 1});
        }

        j = lyn1[i];
        l = i - 1 - lcs(i - 1, j) + 1, r = j + 1 + lcp(i, j + 1) - 1,p = j - i + 1;
        if(r - l + 1 >= 2 * (j - i + 1)){
            runs.push_back({l, r, p});
            //runs.push_back({l,r,j - i + 1});
        }
    }

    sort(runs.begin(),runs.end());
    runs.erase(unique(runs.begin(),runs.end()),runs.end());

    vector<array<int,3>>nruns;
    for(int i = 0;i < runs.size();i++){
        if(i == 0 || runs[i][0] != runs[i - 1][0] || runs[i][1] != runs[i - 1][1])nruns.push_back(runs[i]);
    }
    runs = move(nruns);

    for(int i = 0;i + 1< runs.size();i++){
        assert(runs[i][0] != runs[i + 1][0] || runs[i][1] != runs[i + 1][1]);
    }

    cout<<runs.size()<<endl;
    for(auto &[l,r,p] : runs){
        cout<<l + 1<<" "<<r + 1<<" "<<p<<"\n";
    }
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