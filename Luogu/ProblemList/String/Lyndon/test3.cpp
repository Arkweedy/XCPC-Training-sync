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
    s += ' ';
    vector<ull>hs1(n), b1(n);
    vector<ull>hs2(n), b2(n);
    constexpr ull base1 = 131, base2 = 13331;
    hs1[0] = s[0];
    b1[0] = 1;
    hs2[0] = s[0];
    b2[0] = 1;
    for(int i = 1;i < n;i++){
        hs1[i] = hs1[i - 1] * base1;
        b1[i] = b1[i - 1] * base1;
        hs1[i] += s[i];
        hs2[i] = hs2[i - 1] * base2;
        b2[i] = b2[i - 1] * base2;
        hs2[i] += s[i];
    }

    

    auto get = [&](int l, int r)->pair<ull,ull>
    {
        return make_pair(hs1[r] - (l > 0 ? hs1[l - 1] * b1[r - l + 1] : 0), hs2[r] - (l > 0 ? hs2[l - 1] * b2[r - l + 1] : 0));
    };

    auto lcp = [&](int x, int y)->int //return len(lcp(x, y))
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

    auto lcs = [&](int x, int y)->int //return len(lcs(x, y))
    {
        if(x < 0 || y < 0)return 0;
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


    // === Module C: blogger-style extend from L-root and collect runs ===
    vector<array<int,3>> runs;

    // chk(u, v): 其中 u=i（L-root 的起点），v=j+1（L-root 的后一个位置）
    // p = v-u；左扩 = LCS(u-1, v-1)；右扩 = LCP(u, v)
    auto chk = [&](int u, int v) {
        int p = v - u;
        if (p <= 0) return;
        int tl = lcs(u - 1, v - 1);     // 左扩长度
        int tr = lcp(u, v);             // 右扩长度
        if (tl + tr >= p) {
            int L = u - tl;
            int R = (v - 1) + tr;
            runs.push_back({L, R, p});
        }
    };

    for (int i = 0; i < n; ++i) {
        // 来自两个方向的 Lyndon 根
        chk(i, lyn0[i] + 1);
        chk(i, lyn1[i] + 1);
    }
// === end Module C ===


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