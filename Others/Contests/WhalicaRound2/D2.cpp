#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D2.cpp Create time : 2026.02.15 17:27


class trie {
    static const int N = 3e5;//pool
    static const int n = 6;//range 
    int tree[N][n] = { 0 };
    int cnt[N] = { 0 };
    int tot = 1;

public:

    void insert(vector<int>& s, int root = 0, int pos = 0)
    {
        int x = s[pos];
        if (tree[root][x] == 0) {
            tree[root][x] = tot++;
        }
        cnt[tree[root][x]]++;
        if (pos + 1 != s.size()) {
            insert(s, tree[root][x], pos + 1);
        }
        return;
    }

    i64 query(vector<int>& s, int root = 0, int pos = 0)
    {
        if (pos == s.size())return 0;
        int x = s[pos];
        if (tree[root][x] == 0)return 0;
        else return cnt[tree[root][x]] + query(s, tree[root][x], pos + 1);
    }

    void clear()
    {
        for (int i = 0; i <= tot; i++) {
            for (int j = 0; j < n; j++) {
                tree[i][j] = 0;
            }
            cnt[i] = 0;
        }
        tot = 1;
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

    vector<vector<int>>s(n);
    auto get = [&](string s)->vector<int>
    {
        vector<int>a(s.length());
        for(int i = 0;i < s.length();i++){
            a[i] = alp[s[i]];
        }
        return a;
    };
    for(int i = 0;i < n;i++){
        string t;
        cin >> t;
        s[i] = get(t);
    }

    int k = 0;
    auto ne = [&](vector<int>a)->vector<int>
    {
        int n = a.size();
        for(int i = 0;i < n;i++){
            a[i] = (a[i] + k) % 6;
        }
        return a;
    };

    trie tr;
    for(int i = 0;i < n;i++){
        tr.insert(s[i]);
    }

    while(q--){
        int op;
        cin >> op;
        if(op == 1){
            string t;
            cin >> t;
            auto vt = ne(get(t));
            i64 ans = tr.query(vt);
            cout << ans << "\n";
        }
        else{
            k = (k - 1 + 6) % 6;
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