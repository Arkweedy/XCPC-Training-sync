#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.15 17:05

class Hash
{
    static constexpr int P1 = 1000000007;
    static constexpr int P2 = 1000000009;

    static constexpr int b1 = 131;
    static constexpr int b2 = 13331;

    int n;
    int rb1, rb2;
    bool use_random_base;

    // int rp1, rp2;
    // bool use_random_mod;

    vector<int>h1,p1,h2,p2;

public:

    Hash(vector<int> s)//default 
    {
        n = s.size();
        h1.resize(n);
        p1.resize(n);
        h2.resize(n);
        p2.resize(n);

        p1[0] = 1;
        h1[0] = s[0];
        p2[0] = 1;            
        h2[0] = s[0];
        for (int i = 1; i < n; ++i) {
            p1[i] = 1ll * p1[i-1] * b1 % P1;
            p2[i] = 1ll * p2[i-1] * b2 % P2;
            h1[i] = (1ll * h1[i-1] * b1 + s[i]) % P1;
            h2[i] = (1ll * h2[i-1] * b2 + s[i]) % P2;
        }
    }

    pair<int,int> get(int l, int r)
    {
        int hs1 = h1[r], hs2 = h2[r];
        if(l)hs1 -=  1ll * h1[l - 1] * p1[r - l + 1] % P1, hs2 -= 1ll * h2[l - 1] * p2[r - l + 1] % P2;
        if(hs1 < 0)hs1 += P1;
        if(hs2 < 0)hs2 += P2;
        return make_pair(hs1,hs2);
    }

    int lcp(int x, int y)
    {
        int l = 0, r = min(n - x, n - y) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(get(x, x + m - 1) == get(y, y + m - 1)){
                l = m;
            }
            else{
                r = m;
            }
        }
        return l;
    }

    int lcs(int x, int y)
    {
        int l = 0, r = min(x + 1, y + 1) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(get(x - m + 1, x) == get(y - m + 1, y)){
                l = m;
            }
            else{
                r = m;
            }
        }
        return l;
    }

    int lcp(Hash& t)
    {
        cerr <<"calc lcp "<<endl;
        int l = 0, r = min(n, t.n) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(get(0, m) == t.get(0, m)){
                l = m;
            }
            else{
                r = m;
            }
        }
        cerr << "ok" << endl;
        return l;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    
    //whalic
    vector<int>alp(256);
    alp['w'] = 0;
    alp['h'] = 1;
    alp['a'] = 2;
    alp['l'] = 3;
    alp['i'] = 4;
    alp['c'] = 5;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin >> s[i];
    }
    vector<array<vector<int>, 6>>a(n);
    vector<vector<Hash>>h(n);

    auto get = [&](string s)->vector<int>
    {
        vector<int>a(s.length());
        for(int i = 0;i < s.length();i++){
            a[i] = alp[s[i]];
        }
        return a;
    };

    for(int i = 0;i < n;i++){
        int len = s[i].length();
        a[i][0] = get(s[i]);
        for(int j = 1;j < 6;j++){
            for(int k = 0;k < len;k++){
                a[i][j][k] = (a[i][0][k] + j) % 6;
            }
        }
        for(int j = 0;j < 6;j++){
            h[i].emplace_back(Hash(a[i][j]));
        }
    }

    cerr << "ok" << endl;

    int k = 0;
    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            int res = 0;
            string t;
            cin >> t;
            auto vt = get(t);
            Hash th(vt);
            for(int i = 0;i < n;i++){
                res += th.lcp(h[i][k]);
            }
            cout << res << "\n";
        }
        else if(op == 2){
            k++;
            k %= 6;
        }
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