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

vector<int> Zfunc1(const string& t)
{
    int n = int(t.size());

    string s;
    s.reserve(n + 1);
    s.push_back('#');
    s += t;

    vector<int> z(n + 1, 0);

    if (n == 0) return z;

    z[1] = n;

    for (int i = 2, l = 1, r = 1; i <= n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l + 1]);
        }

        while (i + z[i] <= n && s[1 + z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

constexpr int P = 998244353;

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    KMP kmp(s);
    auto& pi = kmp.fail;
    auto z = Zfunc1(s);

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
    vector<vector<int>>pdp(sq, {1});// 
    dp[0] = 1;
    for(int i = 1;i <= n;i++){
        int p = i;
        while(pi[slink[i]] >= milen){
            
        }
    }
    // dp[0] = 1;
    // for(int i = 1;i <= n;i++){
    //     int len = z[i];
    //     for(auto x : tr){
    //         if(x <= len){
    //             dp[i + x - 1] = (dp[i + x - 1] + dp[i - 1]) % P;
    //         }
    //     }
    // }
    // cout << dp[n] << endl;

    

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