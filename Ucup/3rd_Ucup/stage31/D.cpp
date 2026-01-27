#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.24 10:31:30

array<int,10>get(i64 n)
{
    array<int,10>num = {0};
    while(n){
        num[n % 10]++;
        n /= 10;
    }
    return num;
}

int digit(i64 n)
{
    int cnt = 0;
    while(n){
        cnt++;
        n /= 10;
    }
    return cnt;
}

void solve()
{
    i64 n;
    cin >> n;
    auto num = get(n);
    auto d = digit(n);
    int ans = 0;
    for(int i = 2;i <= 9;i++){
        if(n % i == 0){
            i64 m = n / i;
            if(num == get(m) && d == digit(m)){
                ans++;
            }
        }
    }
    cout << ans << "\n";
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