#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.08.16 11:29

constexpr int P1 = 912165899, P2 = 1e9 + 9;
constexpr int b1 = 2309449, b2 = 961342087;
constexpr int inf = 1e9;

struct segtree{
    int n;
    vector<int>tl,tr;

    segtree(int n_){
        n = n_;
        tl.resize(n * 4, inf);
        tr.resize(n * 4, inf);
    }

    void applyL(int s, int t, int val, int l, int r, int p)
    {
        if(s <= l && r <= t){
            tl[p] = min(tl[p], val);
            return;
        }
        int m = l + r >> 1;
        if(s <= m)applyL(s, t, val, l, m, p * 2);
        if(t > m)applyL(s, t, val, m + 1, r, p * 2 + 1);
        return;
    }

    void applyR(int s, int t, int val, int l, int r, int p)
    {
        if(s <= l && r <= t){
            tr[p] = min(tr[p], val);
            return;
        }
        int m = l + r >> 1;
        if(s <= m)applyR(s, t, val, l, m, p * 2);
        if(t > m)applyR(s, t, val, m + 1, r, p * 2 + 1);
        return;
    }

    int queryL(int pos, int l, int r, int p)
    {
        if(l == r){
            return tl[p];
        }
        int m = l + r >> 1;
        if(pos <= m)return min(tl[p], queryL(pos, l, m, p * 2));
        else return min(tl[p], queryL(pos,  m + 1, r, p * 2 + 1));
    }

    int queryR(int pos, int l, int r, int p)
    {
        if(l == r){
            return tr[p];
        }
        int m = l + r >> 1;
        if(pos <= m)return min(tr[p], queryR(pos, l, m, p * 2));
        else return min(tr[p], queryR(pos,  m + 1, r, p * 2 + 1));
    }

    void applyL(int l, int r, int val)
    {
        if(r < l)return;
        applyL(l, r, val, 0, n - 1, 1);
    }

    void applyR(int l, int r, int val)
    {
        if(r < l)return;
        applyR(l, r, val, 0, n - 1, 1);
    }

    int queryR(int p)
    {
        return queryR(p, 0, n - 1, 1);
    }

    int queryL(int p)
    {
        return queryL(p, 0, n - 1, 1);
    }

};


void solve()
{
    int n;
    cin >> n;
    vector<int>s(n);
    for(int i = 0;i < n;i++){
        cin >> s[i];
    }
    vector<int>p1(n),h1(n),p2(n),h2(n);
    p1[0] = p2[0] = 1;
    h1[0] = h2[0] = s[0];
    for(int i = 1;i < n;i++){
        p1[i] = 1ll * p1[i - 1] * b1 % P1;
        p2[i] = 1ll * p2[i - 1] * b2 % P2;
        h1[i] = (1ll * h1[i - 1] * b1 + s[i]) % P1;
        h2[i] = (1ll * h2[i - 1] * b2 + s[i]) % P2;
    }

    auto get = [&](int l, int r)->pair<int,int>
    {
        int hs1 = h1[r], hs2 = h2[r];
        if(l){
            hs1 -= 1ll * h1[l - 1] * p1[r - l + 1] % P1;
            hs2 -= 1ll * h2[l - 1] * p2[r - l + 1] % P2;
        }
        if(hs1 < 0)hs1 += P1;
        if(hs2 < 0)hs2 += P2;
        return make_pair(hs1, hs2);
    };

    auto lcp = [&](int x, int y)->int
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
    };

    auto lcs = [&](int x, int y)->int
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
    };

    auto get_lyndon = [&](bool order)->vector<int>
    {
        vector<int>lyn(n);
        stack<int>stk;
        for(int i = n - 1;i >= 0;i--){
            lyn[i] = i;
            while(!stk.empty()){
                int j = stk.top();
                int len = lcp(i, j);
                if(order == 0){
                    if(s[i + len] > s[j + len]){
                        lyn[i] = j - 1;
                        break;
                    }
                    else{
                        lyn[i] = lyn[j];
                        stk.pop();
                    }
                }
                else{
                    if(s[i + len] < s[j + len]){
                        lyn[i] = j - 1;
                        break;
                    }
                    else{
                        lyn[i] = lyn[j];
                        stk.pop();
                    }
                }
            }
            stk.push(i);
        }
        return lyn;
    };

    auto lyn0 = get_lyndon(0);
    auto lyn1 = get_lyndon(1);

    vector<array<int, 3>>runs;
    for(int i = 0;i < n;i++){
        int j,l,r,p;
        j = lyn0[i];
        l = i - 1 - lcs(i - 1, j) + 1, r = j + 1 + lcp(i, j + 1) - 1, p = j - i + 1;
        if(r - l + 1 >= 2 * (j - i + 1)){
            runs.push_back({l, r, p});
        }
        j = lyn1[i];
        l = i - 1 - lcs(i - 1, j) + 1, r = j + 1 + lcp(i, j + 1) - 1, p = j - i + 1;
        if(r - l + 1 >= 2 * (j - i + 1)){
            runs.push_back({l, r, p});
        }
    }

    sort(runs.begin(),runs.end());
    runs.erase(unique(runs.begin(),runs.end()), runs.end());
    

    //cerr << "OK" << endl;

    // 
    int sq = sqrt(n) + 1;
    vector<int>minp2(n, n), maxp3(n, -1);
    segtree t(n);
    //cerr << "OK" << endl;
    //vector<vector<int>>d2(sq + 1, vector<int>(n)),d3(sq + 1, vector<int>(n));
    for(auto [l, r, p] : runs){
        t.applyR(l, r - p * 2 + 1, p * 2);
        t.applyL(l + p * 3 - 1, r, p * 3);
    }

    //cerr << "OK" << endl;

    for(int i = 0;i < n;i++){
        minp2[i] = min(t.queryR(i) + i - 1, n);
        maxp3[i] = max(i - t.queryL(i) + 1, -1);
        //cerr << t.queryL(i) << " ";
    }
    //cerr << endl;
    
    // for(int i = 0;i < n;i++){
    //     cerr << minp2[i] << " ";
    // }
    // cerr << endl;
    // for(int i = 0;i < n;i++){
    //     cerr << maxp3[i] << " ";
    // }
    // cerr << endl;


    vector<int>L(n, n);
    for(int i = 0;i < n - 1;i++){
        if(maxp3[i] >= 0 && minp2[i + 1] < n){
            L[maxp3[i]] = min(L[maxp3[i]], minp2[i + 1]);
        }
    }
    for(int i = n - 2;i >= 0;i--){
        L[i] = min(L[i], L[i + 1]);
    }


    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        if(r >= L[l]){
            cout << "Yes" << "\n";
        }
        else{
            cout << "No" << "\n";
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