#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;

using namespace std;

//Create time: 2026.08.11 13:50:52
constexpr int P = 998244353;

void solve()
{
    int n, x;
    cin >> n >> x;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    i128 sum = 0;
    for(int i = 0;i < n;i++){
        sum += a[i] / x;
        a[i] %= x;
    }
    if(x == 1){
        cout << i64(sum % P) << endl;
        return;
    }
    sort(a.begin(),a.end(), greater<>());
    for(int i = 0;i < n;i++){
        if(sum + 1 >= x - a[i]){
            sum += 1;
            sum -= x - a[i];
            a[i] = 0;
        }
    }
    i128 ans = 0;
    for(int i = 0;i < n;i++){
        ans += a[i];
    }
    sum %= (x - 1);
    ans += sum;
    cout << i64(ans % P) << endl;
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