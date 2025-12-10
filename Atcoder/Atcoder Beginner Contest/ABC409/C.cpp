#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,L;
    cin>>n>>L;
    vector<int>cnt(L + 1);
    vector<int>a(n);
    for(int i = 1;i < n;i++){
        cin>>a[i];
        a[i] = (a[i] + a[i - 1])%L;
    }
    for(int i = 0;i < n;i++){
        cnt[a[i]]++;
    }
    if(L % 3 != 0){
        cout<<0<<endl;
        return;
    }
    ll ans = 0;
    for(int i = 0;i < L / 3 ;i++){
        ans += 1ll * cnt[i] * cnt[i + L / 3] * cnt[i + L / 3 * 2];
    }
    cout<<ans<<endl;
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