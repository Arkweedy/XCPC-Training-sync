#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//B.cpp Create time : 2025.12.18 15:33

std::vector<int> zFunction(std::string s) {
    int n = s.size();
    std::vector<int> z(n + 1);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = std::max(0, std::min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}

constexpr int P = 998244353;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    auto z = zFunction(s);
    vector<int>v(n + 1), v2(n + 1);
    for(int i = 0;i < n;i++){
        if(z[i] + i == n){
            v[z[i]] += z[i];
            v2[z[i]] += 1ll * z[i] * z[i] % P;
        }
    }
    for(int i = 1;i <= n;i++){
        v[i] = (v[i] + v[i - 1]) % P;
        v2[i] = (v2[i] + v2[i - 1]) % P;
    }
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        ans = (ans + 1ll * (i + 1) * v2[z[i]] % P + 1ll * i * (i + 1) % P * v[z[i]] % P) % P;
    }
    cout << ans << endl;
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