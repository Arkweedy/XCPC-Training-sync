#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    constexpr int N = 200000;
    int n;
    cin>>n;
    vector<int>a(n);
    array<int,200005>c{0};
    for(int i = 0;i < n;i++){
        cin>>a[i];
        c[a[i]]++;
    }
    for(int i = 1;i <= N ;i++){
        c[i] += c[i - 1];
    }
    sort(a.begin(),a.end());
    int ma = *max_element(a.begin(),a.end());
    ll ans = 0;

    auto occ = [&](int x)->int
    {
        return c[x] - c[x - 1];
    };

    for(int i = 0;i < n - 2;i++){
        for(int j = i + 1;j < n - 1;j++){
            if(a[i] == a[j])continue;
            int l = ma - (a[i] + a[j]) + 1 , r = a[i] + a[j] - 1;
            l = max(l, a[j] + 1);
            if(l <= r){
                ans += c[r] - c[l - 1];
            }
        }
    }
    cerr<<ans<<endl;
    map<int,int>vs;
    for(int i = 0;i < n;i++){
        int oc = c[a[i]] - c[a[i] - 1];
        if(oc > 1 && !vs[a[i]]){
            vs[a[i]] = 1;
            int l = ma - (a[i] + a[i]) + 1, r = a[i] + a[i] - 1;
            ll x = oc * (oc - 1) / 2;
            if(l <= r){
                ans += c[r] * x;
                if(l > 0)ans -= c[l - 1] * x;
                if(a[i] >= l && a[i] <= r) ans -= oc * x;
            }

            if(oc > 2 && a[i] * 3 > ma){
                int xx = oc;
                ans += 1ll * xx * (xx - 1) * (xx - 2) / 6;
            }
        }
        
    }
    cout<<ans<<endl;
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