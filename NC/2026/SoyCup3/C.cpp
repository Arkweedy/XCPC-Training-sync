#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;

using namespace std;

//Create time: 2026.08.03 11:27:22
i64 P;

i64 power(i64 a, i64 p)
{
    i128 res = 1;
    while(p){
        if(p & 1)res = (i128)res * a % P;
        a = (i128)a * a % P;
        p >>= 1;
    }
    return res;
}

i64 inv(i64 a)
{
    return power(a, P - 2);
}

//constexpr int P = 998244353;

void solve()
{
    // i64 n, p;
    // cin >> n >> p;
    // i64 ans = (n / 2 % P) * ((n / 2 - 1) % P) % P;
    // if(n % 2 == 1)ans = (ans + n / 2) % P;
    // if(n * 2 + 1 >= p)ans = (ans - ((p - 1) / 2 - 1) / 2 + P) % P;
    // cout << ans << endl;


    i64 n;
    cin >> n >> P;
    int sum = 0;
    for(int b = 1;b <= n;b++){
        
        int cnt = 0;
        for(int a = 1;a < b;a++){
            if(i128(a) * P > i128(a) * inv(b) % P * b){
                //cout << a << " ";
                cnt++;
            }
        }
        //cout << "#" << b << " " << cnt << endl;
        //cout << "#" << b << " " << cnt << " " << P % b - b << " " << gcd(P + 1, b) << endl;
        cout << cnt << " " << (b - gcd(P + 1, b)) << endl;
        sum += cnt;
    }
    cerr << sum << endl;
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