#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.03.06 12:59

void solve()
{
    int n, k, m, c, d;
    cin >> n >> k >> m >> c >> d;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    
    constexpr int inf = 1e9;
    auto check = [&](i64 x)->bool
    {
        vector<i64>b(n);
        for(int i = 0;i < n;i++){
            if(a[i] >= x)b[i] = -1;
            else if(d == 0)b[i] = a[i] + c >= x ? 0 : inf;
            else if(a[i] + c >= x)b[i] = 0; //
            else b[i] = (x - a[i] - c + d - 1) / d;
        }
       
        vector<int>f(n + 1);
        for(int i = 0;i < n;i++){
            if(b[i] == -1){
                f[0]++;
            }
            else if(b[i] < m){
                f[max(i - m + 1, 0)]++;
                f[max(i - b[i] + 1, 0ll)]--;
            }
            else{
                continue;
            }
        }
        
        int res = f[0];
        for(int i = 1;i < n;i++){
            f[i] += f[i - 1];
            res = max(res, f[i]);
        }
        if(res >= k){
            return true;
        }
        else{
            return false;
        }
    };

    i64 l = 0, r = 1e15;
    while(r - l > 1){
        i64 mid = l + r >> 1;
        if(check(mid)){
            l = mid;
        }
        else{
            r = mid;
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
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}