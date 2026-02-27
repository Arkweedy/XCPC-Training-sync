#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.27 15:58

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    // all -> \binom{n}{2}
    // if(lca (i, j) == i / j -> j - i)
    // elsed lca(i, j) = k 
    vector<int>ans(n);
    vector<int>l(n),r(n),c(n);
    vector<int>d(n + 1);
    // lca(i, j) = i/j -> 
    auto calc1 = [&](auto&&self, int l, int r)->void
    {
        if(l == r + 1)return;
        if(l == r){
            c[l] = 1;
            return;
        }
        int m = l + r >> 1;
        self(self, l, m - 1);
        self(self, m + 1, r);
        

    };

    vector<int>cache(n + 1);
    auto calc2 = [&](auto&&self, int n, int w)->void
    {
        if(n <= 2)return;
        int lc = (n - 1) / 2, rc = n / 2;
        if(lc == rc)self(self, lc, w * 2);
        else{
            self(self, lc, w);
            self(self, rc, w * 2);
        }

    };
     
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