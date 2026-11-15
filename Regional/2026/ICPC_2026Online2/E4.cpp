#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;
using namespace std;

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

    map<int,i64>dp;
    dp[1] = 1;
    for(auto [p, c] : fac){
        // cnt: (order, number of elements) modulo p^c.
        vector<pair<int,int>>cnt;
        if(p == 2){
            cnt.push_back({1, 1});
            if(c == 2){
                cnt.push_back({2, 1});
            }
            if(c >= 3){
                cnt.push_back({2, 3});
                for(int i = 2;i <= c - 2;i++){
                    int x = 1 << i;
                    cnt.push_back({x, x});
                }
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
                    cnt.push_back({x, phi});
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

        // CRT: multiply counts, take the lcm of orders.
        map<int,i64>ndp;
        for(auto [x, cx] : dp){
            for(auto [y, cy] : cnt){
                int z = x / gcd(x, y) * y;
                ndp[z] += cx * cy;
            }
        }
        dp.swap(ndp);
    }

    i64 ans = 0;
    for(auto [x, c] : dp){
        ans += 1ll * x * c;
    }
    cout << ans << endl;
    return;

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}



