#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.11.07 23:09

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<int>ex(n * 3 + 1);
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        ex[x]++;
    }

    i64 ans = 0;
    constexpr int D = 3;
    array<array<array<array<int, D>, 4>, 4>, 4>dp{}; 
    // -3, - 2, -1, neg
    // 0, 1, 2, 3->noex
    dp[3][3][3][0] = 1;
    for(int i = 1;i <= n * 3;i++){
        array<array<array<array<int, D>, 4>, 4>, 4>ndp{}; 
        for(int a = 0;a <= 3;a++){
            for(int b = 0;b <= 3;b++){
                for(int c = 0;c <= 3;c++){
                    if(ex[i]){
                        int delta = 0;
                        if(a == 0 || a == 2)delta++;
                        int na, nb, nc;
                        if(b <= 2)na = b + 1;
                        else na = 3;
                        if(c <= 2)nb = c + 1;
                        else nb = 3;
                        nc = 0;
                        for(int d = 0;d + delta < D;d++){
                            ndp[na][nb][nc][d + delta] += dp[a][b][c][d];
                            ndp[na][nb][nc][d + delta] %= P;
                        }
                    }
                    //empty
                    {
                        int delta = 0;
                        if(a == 0 || a == 1)delta++;
                        int na, nb, nc;
                        if(b <= 2)na = b;
                        else na = 3;
                        if(c <= 2)nb = c;
                        else nb = 3;
                        nc = 3;
                        for(int d = 0;d + delta < D;d++){
                            ndp[na][nb][nc][d + delta] += dp[a][b][c][d];
                            ndp[na][nb][nc][d + delta] %= P;
                        }
                    }
                }
            }
        }
        dp = move(ndp);
    }

    for(int a = 0;a <= 3;a++){
        for(int b = 0;b <= 3;b++){
            for(int c = 0;c <= 3;c++){
                for(int d = 0; d <= 2;d++){
                    int neg = d + (a < 2) + (b < 2) + (c < 2);
                    if(neg <= 2){
                        ans += dp[a][b][c][d];
                    }
                }
            }
        }
    }
    ans--; // empty
    ans = (ans + P) % P;
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