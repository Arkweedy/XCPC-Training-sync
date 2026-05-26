#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.05.16 22:48



void solve()
{
    i64 a, n;
    cin >> a >> n;
    vector<int>c(10);
    int ma = 0, mi = 9;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        c[x] = 1;
        ma = max(ma, x);
        mi = min(mi, x);
    }

    vector<int>l(10, -1), r(10, -1);
    int p = -1;
    for(int i = 0;i < 10;i++){
        l[i] = p;
        if(c[i]){
            p = i;
        }
    }
    p = -1;
    for(int i = 9;i >= 0;i--){
        r[i] = p;
        if(c[i]){
            p = i;
        }
    }

    vector<i64>d;
    while(a){
        d.push_back(a % 10);
        a /= 10;
    }

    if(d.empty()){
        cout << mi << endl;
        return;
    }

    d.push_back(0);

    vector<i64>base(d.size() + 1);
    base[0] = 1;
    for(int i = 0;i < d.size();i++){
        base[i + 1] = base[i] * 10;
    }
    vector<i64>b2 = base;
    for(int i = 0;i < d.size();i++){
        b2[i + 1] += b2[i];
    }
    vector<i64>v = d;
    for(int i = 0;i < d.size() - 1;i++){
        v[i + 1] = v[i] + base[i + 1] * v[i + 1];
    }

    auto calc = [&](int x, int k)->i64
    {
        if(k == 0)return 0;
        return b2[k - 1] * x;
    };

    constexpr i64 inf = 2e18;
    i64 ans = inf;
    int lead = 1;
    for(int i = d.size() - 1;i >= 0;i--){
       
        int x = d[i];
        int lv = l[x];
        if(lv == -1 && x > 0 && lead && i != 0)lv = 0;
        if(lv != -1){
            i64 lc = base[i] * lv + calc(ma, i);
            ans = min(ans, v[i] - lc);
        }
        int rv = r[x];
        if(rv != -1){
            i64 rc = base[i] * rv + calc(mi, i);
            ans = min(ans,  rc - v[i]);
        }
        if(i == 0 && c[x])ans = 0;
        if(c[x] || (x == 0 && lead)){
            //
        }
        else{
            break;
        }
        if(x != 0)lead = 0;
    }
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