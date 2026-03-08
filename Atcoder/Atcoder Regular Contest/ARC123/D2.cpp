#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.03.03 17:06

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<i64>b(n), c(n);
    if(a[0] > 0)c[0] = a[0];
    else b[0] = a[0];
    for(int i = 1;i < n;i++){
        if(a[i] >= a[i - 1]){
            b[i] = b[i - 1] + a[i] - a[i - 1];
            c[i] = c[i - 1];
        }
        else{
            b[i] = b[i - 1];
            c[i] = c[i - 1] + a[i] - a[i - 1];
        }
    }
    // for(int i = 0;i < n;i++){
    //     cerr << b[i] << " ";
    // }
    // cerr << endl;
    // for(int i = 0;i < n;i++){
    //     cerr << c[i] << " ";
    // }
    // cerr << endl;

    auto calc = [&](i64 x)->i64
    {
        i64 ans = 0;
        for(int i = 0;i < n;i++){
            ans += abs(b[i] + x);
            ans += abs(c[i] - x);
        }
        return ans;
    };

    constexpr i64 N = 1e13 + 10;
    i64 l = -N, r = N;
    while(r - l > 2){
        i64 ml = l + (r - l) / 3, mr = l + (r - l) * 2 / 3;
        i64 lres = calc(ml), rres = calc(mr);
        //cerr << l << " " << r << " "<< lres << " " << rres << endl;
        if(lres <= rres){
            r = mr;
        }
        else{
            l = ml;
        }
    }
    i64 ans = min(min(calc(l), calc(l + 1)), calc(l + 2));
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