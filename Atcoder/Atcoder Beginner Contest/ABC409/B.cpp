#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end());
    int l = -1,r = 1e9+7;
    while(r -l > 1){
        int m = l + r >> 1;
        int p = lower_bound(a.begin(),a.end(),m) - a.begin();
        int cnt = n - p;
        if(cnt >= m){
            l = m;
        }else{
            r = m;
        }
    }
    cout<<l<<endl;
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