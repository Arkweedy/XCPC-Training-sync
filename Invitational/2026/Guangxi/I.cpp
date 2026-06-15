#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.03 00:00:34
struct KMP
{
    string s;
    vector<int>fail;
    vector<int>slink;
    vector<int>diff;
    vector<vector<int>>ot;
    int suff;

    KMP(){init();}
    KMP(string& ss){init();for(auto ch :ss)add(ch);}

    void init()
    {
        suff = 0;
        s += '#';
        fail.assign(1, 0);
        slink.assign(1, -1);
        diff.assign(1, -1);
        ot.emplace_back();
    }
    

    void newNode()
    {
        fail.emplace_back();
        diff.emplace_back();
        slink.emplace_back();
        ot.emplace_back();
    }

    void add(char c)
    {
        s += c;
        newNode();
        int last = s.length() - 1;
        int cur = suff;
        while(cur != 0 && s[cur + 1] != s[last]){
            cur = fail[cur];
        }
        if(s[last] == s[cur + 1] && last != 1)fail[last] = cur + 1;
        else fail[last] = cur;
        diff[last] = last - fail[last];
        slink[last] = diff[last] == diff[fail[last]] ? slink[fail[last]] : fail[last];
        ot[fail[last]].push_back(last);
        suff = fail[last];
    }
    
};

constexpr int P = 998244353;

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    KMP kmp(s);
    auto& pi = kmp.fail;
    auto& slink = kmp.slink;
    auto& diff = kmp.diff;

    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        if(pi[i] == 0 || pi[i] * 2 < i){
            a[i] = 0;
        }
        else{
            a[i] = a[pi[i]] + 1;
        }
    }
    // k trans
    int milen = n + 1;
    for(int i = 1;i <= n;i++){
        if(a[i] >= k){
            milen = min(milen, pi[i]);
        }
    }

    int sq = sqrt(n);
    vector<int>dp(n + 1);
    vector<vector<int>>pdp(sq + 1, vector<int>(n + 1));// diff - d ,presum
    for(int i = 0;i <= sq;i++){
        pdp[i][0] = 1;
    }

    auto getLR = [&](int d, int l, int r)->int // [l, r]
    {
        assert((r - l) % d == 0);
        if(d <= sq){
            if(r < 0)return 0;
            if(l < d)return pdp[d][r];
            int res = (pdp[d][r] - pdp[d][l - d] + P) % P;
            return res;
        }
        else{
            int res = 0;
            for(int i = l;i <= r;i += d){
                res = (res + dp[i]) % P;
            }
            return res;
        }
    };

    dp[0] = 1;
    for(int i = 1;i <= n;i++){
        // on slink list, not strictly increasing
        // so check all block
        for(int p = i; p > 0;p = slink[p]){ 
            if(a[p] < k)continue;
            int d = diff[p], v = slink[p] + d;
            int low = v + max(k - a[v], 0) * d;
            int l = i - p, r = i - low;
            dp[i] = (dp[i] + getLR(d, l, r)) % P;
        }

        for(int j = 1;j <= sq;j++){
            pdp[j][i] = dp[i];
            if(i >= j)pdp[j][i] = (pdp[j][i] + pdp[j][i - j]) % P;
        }
    }
    
    cout << dp[n] << endl;

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