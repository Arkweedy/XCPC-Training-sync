#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.09.18 23:11

void solve()
{
    int n;
    cin >> n;
    vector<pair<int,int>>fac;
    for(int i = 2;i * i <= n;i++){
        int c = 0;
        while(n % i == 0){
            n /= i;
            c++;
        }
        if(c != 0){
            fac.push_back({i, c});
        }
    }

    if(n != 1){
        fac.push_back({n, 1});
    }

    map<int,i64>mp;
    vector<vector<int>>a2 = {
        {1},
        {1,0},
        {1,1,0},
        {1,3,0,0},
    };
    mp[1] = 1;
    for(auto [p, c] : fac){
        vector<pair<int,int>>f;
        if(p == 2){
            f.resize(c + 1);
            for(int i = 0;i <= c;i++){
                if(c <= 2)f[i] = make_pair(1 << i, a2[c][i]);
                else if(i < 2)f[i] = make_pair(1 << i, a2[3][i]);
                else f[i] = make_pair(1 << i, i >= c - 1 ? 0 : (1 << i));
            }
        }
        else{
            int phin = p - 1;
            for(int i = 0;i < c - 1;i++){
                phin *= p;
            }
            vector<pair<int,int>>pfac;
            for(int i = 2;i * i <= phin;i++){
                int c = 0;
                while(phin % i == 0){
                    phin /= i;
                    c++;
                }
                if(c != 0){
                    pfac.push_back({i, c});
                }
            }
            if(phin != 1){
                pfac.push_back({phin, 1});
            }
            int m = pfac.size();
            auto dfs = [&](auto&&self, int p, int x, int phi)->void
            {
                if(p == m){
                    f.emplace_back(x, phi);
                    return;
                }
                auto [q, c] = pfac[p];
                int y = 1;
                int py = 1;
                for(int i = 0;i <= c;i++){
                    self(self, p + 1, x * y, phi * py);
                    if(i == c)break;
                    if(i == 0)py *= (q - 1);
                    else py *= q;
                    y *= q;
                }
                return;
            };
            dfs(dfs, 0, 1, 1);
        }
        map<int,i64>nmp;
        for(auto [x, a] : mp){
            for(auto [y, b] : f){
                nmp[lcm(x, y)] += a * b;
            }
        }
        mp = move(nmp);
    }

    i64 ans = 0;
    for(auto [x, c] : mp){
        ans += x * c;
    }
    cout << ans << endl;
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