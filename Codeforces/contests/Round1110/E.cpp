#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.07.17 00:52

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>st(n), cnt(n), sz(n, 1); // cnt mod 2
    auto dfs1 = [&](auto&&self, int p, int fa)->void
    {
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                cnt[p] ^= cnt[s];
                sz[p] += sz[s];
            }
        }
        st[p] = cnt[p];
        if(st[p])cnt[p] ^= 1;//add 1
        return;
    };
    dfs1(dfs1, 0, -1);

    vector<int>fst(n), fcnt(n);
    vector<int>rst(n), rcnt(n);//fa
    auto rdfs = [&](auto&&self, int p, int fa) -> void
    {
        int x = 
        for(auto s : g[p]){

        }
    };

    i64 ans = 0;
    vector<int>outersz(n);
    //in : st, cnt, sz
    //fa : fst(p), fcnt(p), outersz
    auto dfs2 = [&](auto&&self, int p, int fa)->void
    {
        vector<int>s0,s1;
        int sum0 = 0, sum1 = 0;
        for(auto s : g[p]){
            if(s != fa){
                if(st[s] == 0){
                    s0.push_back(s);
                    sum0 += sz[s];
                }
                else{
                    s1.push_back(s);
                    sum1 += sz[s];
                }
            }
            else{

            }
        }

        // rst
        if(rst[p] == 0){//0， 0 + 0， 1 + 1
            for(auto s : s0){
                if(s != fa){
                    ans += sz[s];
                    ans += 1ll * sz[s] * (sum0 - sz[s]);
                    outersz[s] -= sum0 - sz[s];
                }
                else{

                }
            }
        }
        else{// 1， 0 + 1

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