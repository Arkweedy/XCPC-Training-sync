#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ld = long double;

using namespace std;

//Create time: 2025.10.29 20:17:56

void solve()
{
    int n;
    cin>>n;
    vector<ld>a(n);
    ld ma = 0;
    for(int i = 0;i < n;i++){
        int x;
        cin>>x;
        a[i] = x;
        ma = max(ma,a[i]);
    }
    ld l = 0, r = ma * 2 + 1;
    constexpr ld eps = 1e-7;
    auto calc = [&](ld x)->ld
    {
        ld res = 0;
        for(int i = 0;i < n;i++){
            res += min(x * 2, a[i]) - a[i] - x;
        }
        return res;
    };
    while(r - l > eps){
        ld ml = l + (r - l) / 3, mr = l + (r - l) / 3 * 2;
        ld resl = calc(ml), resr = calc(mr);
        if(resl < resr){
            l = ml;
        }
        else{
            r = mr;
        }
    }
    //cerr<<l<<endl;
    ld ans = -calc(l) / n;
    cout<<fixed<<setprecision(10)<<ans<<endl;
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