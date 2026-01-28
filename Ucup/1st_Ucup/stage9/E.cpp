#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;

using namespace std;

//Create time: 2026.01.28 11:05:05

void solve()
{
    int n;
    i64 k;
    cin >> n >> k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    auto check = [&](i64 x)->bool
    {
        vector<i64>need(n);
        for(int i = 0;i < n;i++){
            need[i] = (a[i] + x - 1) / a[i];
        }
        i128 sum = 0;
        for(int i = 0;i < n;i++){
            if(i != n - 1 || need[i] > 0){
                sum++;
                need[i]--;
            }
            if(need[i] > 0){
                if(i + 1 < n){
                    need[i + 1] -= need[i];
                }
                sum += need[i] * 2;
                need[i] = 0;
            }
        }
        return sum <= k;
    };

    i64 l = 0, r = 2e17;
    while(r - l > 1){
        i64 m = l + r >> 1;
        if(check(m)){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout << l << endl;
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