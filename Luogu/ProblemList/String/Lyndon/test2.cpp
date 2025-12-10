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

    // === Module B: blogger-style lyndon-suffix via cmpS/extr（0-based） ===
    auto cmpS = [&](int u, int v)->bool {
        // extr(u,v) 的效果：右向最长公共前缀
        int L = lcp(u, v);
        // 依赖 s[n] 的哨兵（你上面已做 s.push_back(' ')）
        return s[u + L] < s[v + L];
    };

    auto get_lyndon_suffix = [&](bool order)->vector<int> {
        // order==0: 正序；order==1: 反序
        vector<int> ly(n);
        vector<int> st; st.reserve(n + 1);
        st.push_back(n);             // 哨兵：相当于博主的 stk[0]=n+1；用于取前一项
        for (int i = n - 1; i >= 0; --i) {
            while (st.size() > 1 && (cmpS(i, st.back()) == order)) st.pop_back();
            st.push_back(i);
            // ly[i] = 栈中“前一个位置” - 1
            ly[i] = st[st.size() - 2] - 1;
        }
        return ly;
    };
// === end Module B ===


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