#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

struct Suffix_Array {
    int n;
    vector<int> sa, rk, lc;
    vector<vector<int>> st;
    Suffix_Array(string s) {
        n = s.size();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(),
            [&](int a, int b) {
                return s[a] < s[b];
            });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        }
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; i++) {
                tmp.push_back(n - k + i);
            }
            for (auto i : sa) {
                if (i >= k) {
                    tmp.push_back(i - k);
                }
            }
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) {
                cnt[rk[i]]++;
            }
            for (int i = 1; i < n; i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            }
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                rk[sa[i]] = 
                rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            }
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; i++) {
            if (rk[i] == 0) {
                j = 0;
            }
            else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; ) {
                    j++;
                }
                lc[rk[i] - 1] = j;
            }
        }
    }

    void init_lcp()
    {
        constexpr int K = 21;
        st.resize(K, vector<int>(n - 1));
        st[0] = lc;
        for (int j = 0; j < K - 1; j++) {
            for (int i = 0; i + (2 << j) <= n - 1; i++) {
                st[j + 1][i] = min(st[j][i], st[j][i + (1 << j)]);
            }
        }
    }
    
    int rmq(int l, int r) {
        int k = __lg(r - l);
        return min(st[k][l], st[k][r - (1 << k)]);
    };
    int lcp(int i, int j) {
        if (i == j || i == n || j == n) {
            return min(n - i, n - j);
        }
        int a = rk[i];
        int b = rk[j];
        if (a > b) {
            swap(a, b);
        }
        return min({n - i, n - j, rmq(a, b)});
    };
    
    // int lcs(int i, int j) {
    //     if (i == j || i == 0 || j == 0) {
    //         return min(i, j);
    //     }
    //     int a = rk[n + n - i];
    //     int b = rk[n + n - j];
    //     if (a > b) {
    //         swap(a, b);
    //     }
    //     return min({i, j, rmq(a, b)});
    // };
};


void solve()
{
    string s;
    cin>>s;
    Suffix_Array SA(s);
    auto&sa = SA.sa;
    int n = s.length();
    for(int i = 0;i < n;i++){
        cout<<sa[i] + 1<<" ";
    }
    cout<<endl;

    return;

    // int n = s.length();
    // vector<int>sa(n),rk(n * 2 + 1);
    // iota(sa.begin(),sa.end(),0);
    // sort(sa.begin(),sa.end(),[&](int i, int j)->bool
    // {
    //     return s[i] < s[j];
    // });
    // for(int i = 0,p = 0;i < n;i++){
    //     rk[sa[i]] = p;
    //     if(i < n - 1 && s[sa[i]] < s[sa[i + 1]])p++;
    // }
    
    // // cerr<<"sa : ";
    // // for(int i = 0;i < n;i++){
    // //     cerr<<sa[i]<<" ";
    // // }
    // // cerr<<endl;
    // // cerr<<"rk : ";
    // // for(int i = 0;i < n;i++){
    // //     cerr<<rk[i]<<" ";
    // // }
    // // cerr<<endl;
    // for(int i = 1;i < n;i *= 2){
    //     sort(sa.begin(),sa.end(), [&](int a, int b)->bool
    //     {
    //         return rk[a] == rk[b]
    //          ? ((a + i < n ? rk[a + i] : -1) < (b + i < n ? rk[b + i] : -1))
    //          : rk[a] < rk[b];
    //     });
    //     auto ork = rk;
    //     for(int j = 0, p = 0;j < n;j++){
    //         rk[sa[j]] = p;
    //         if(j + 1 < n && (ork[sa[j]] < ork[sa[j + 1]] || ork[sa[j] + i] < ork[sa[j + 1] + i]))p++;
    //     }

    //     // cerr<<"sa : ";
    //     // for(int i = 0;i < n;i++){
    //     //     cerr<<sa[i]<<" ";
    //     // }
    //     // cerr<<endl;
    //     // cerr<<"rk : ";
    //     // for(int i = 0;i < n;i++){
    //     //     cerr<<rk[i]<<" ";
    //     // }
    //     // cerr<<endl;
    // }
    
   
    // for(int i = 0;i < n;i++){
    //     cout<<sa[i] + 1<<" ";
    // }
    // cout<<endl;
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