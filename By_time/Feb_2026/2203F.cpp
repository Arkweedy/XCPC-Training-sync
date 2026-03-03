#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.27 15:58

constexpr int P = 998244353;

void solve() {
    int n;
    cin >> n;  
    map<int,int>v;
    map<int, i64> q;
    q[n] = 1;
    while(!q.empty()){
        auto [len, c] = *q.begin();
        q.erase(q.begin());
        v[len] += c;

        int L = (len - 1) / 2;
        int R = len - L - 1;
        if(L) q[L] += c;
        if(R) q[R] += c;
    }

    // vector<int>cnt(n + 1);
    // int l = n, r = n;
    // int lc = 1, rc = 0; 
    // v[n] = 1;
    // cnt[n] = 1; 
    // while(l != 0){ 
    //     int a = (l - 1) / 2, b = l / 2; 
    //     int c = (r - 1) / 2, d = r / 2; 
    //     l = a, r = d; 
    //     if(l == r){ 
    //         lc = lc * 2 + rc * 2; 
    //         rc = 0; 
    //         v[l] += lc;
    //         cnt[l] = lc; 
    //     } 
    //     else{ 
    //         int nlc = lc, nrc = rc; 
    //         if(b == l)nlc += lc; 
    //         else nrc += lc; 
    //         if(c == l)nlc += rc; 
    //         else nrc += rc; lc = nlc; 
    //         rc = nrc; 
    //         v[l] += lc;
    //         v[r] += rc;
    //         cnt[l] = lc; cnt[r] = rc; 
    //     } 
    // }

    vector<i64>ans(n + 1); 
    map<int,map<int,int>>mp; 
    auto lsz = [&](int x)->int
    {
        return (x - 1) / 2;
    };
    auto rsz = [&](int x)->int
    {
        return x / 2;
    };

    auto mergeto = [&](int a, int b, int p)->void
    {
        for(auto [x, c]: mp[a]){
            mp[p][x] += c;
        }
        for(auto [x, c]: mp[b]){
            mp[p][x] += c;
        }
    }; 

    v.erase(0);

    for(auto [k, c] : v){ 
        int l = (k - 1) / 2, r = k / 2;
        for(int i = 1;i <= l;i++){
            ans[i] += c;
        }
        for(int i = 1;i <= r;i++){
            ans[i] += c;
        }
        for(auto [x, c1] : mp[l]){ 
            for(auto [y, c2] : mp[r]){
                ans[rsz(x) + lsz(y) + 2] += 1ll * c1 * c2 * c; 
            } 
        }
        mergeto(l, r, k);
        mp[k][k]++;
    }
    for(int i = n;i >= 0;i--){
        cout << ans[i] << " ";
    }
    cout << endl;
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