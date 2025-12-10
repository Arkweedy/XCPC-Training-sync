//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 2.1e5 + 10;
constexpr int root = 0;
constexpr int digit = 59;

class trie01 {
    //vector<array<int,2>>tree;
    int tree[N][2] = {0};
    int ord = 0;
    int tot = 1;

public:
    // trie01()
    // {
    //     tree.resize(N,{0,0});
    // }

    void insert(ll x)
    {
        ord++;
        int p = root;
        for (int i = digit; i >= 0; i--) {
            int j = (x >> i) & 1;
            if (tree[p][j] == 0)tree[p][j] = tot++;
            p = tree[p][j];
        }
    }

    ll query_max_xor(ll x)
    {
        int p = root;
        ll res = 0;
        for (int i = digit; i >= 0; i--) {
            ll j = ((x >> i) & 1) ^ 1;
            if (tree[p][j] >= 1) { p = tree[p][j]; res |= 1ll << i; }
            else p = tree[p][j ^ 1];
        }
        return res;
    }
};

void solve()
{
    int n;
    cin>>n;
    vector<ll>a(n + 2);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    int half = min(n / 2, 18);
    ll ans = 0;
    for(int M = half; M <= half + 1;M++){
        trie01 t;
        t.insert(0);
        auto find1 = [&](auto&&self, int p, ll val)->void
        {
            t.insert(val);
            for(int i = p + 2;i <= M;i++){
                self(self,i,val^a[i]);
            }
            return;
        };
        auto find2 = [&](auto&&self, int p, ll val)->void
        {
            if(p == M)t.insert(val);
            for(int i = p + 2;i <= M;i++){
                self(self,i,val^a[i]);
            }
            return;
        };
        auto qry = [&](auto&&self, int p, ll val)->void
        {
            ans = max(ans,t.query_max_xor(val));
            for(int i = p + 2;i <= n;i++){
                self(self,i,val^a[i]);
            }
            return;
        };
        if(M == half)find1(find1,-1,0);//(0, M]
        else find2(find2,-1,0);//(0, M]
        qry(qry, M, 0);//(M + 1, n]
        ans = max(ans, t.query_max_xor(0));
    }
    cout<<ans<<endl;
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