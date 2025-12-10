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
    vector<int>rk(n);
    vector<int>val(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    iota(rk.begin(),rk.end(),0);
    sort(rk.begin(),rk.end(),[&](int i, int j)->bool
    {
        return a[i] < a[j];
    });


   
    for(int i = 0;i < n;i++){
        int k = rk[i];
        val[k] = 1;
        if(k > 0 && a[k] > a[k - 1]){
            val[k] = max(val[k],val[k - 1] + 1);
        }
        if(k < n - 1 && a[k] > a[k + 1]){
            val[k] = max(val[k],val[k + 1] + 1);
        }
    }
    ll ans = 0;
    for(int i = 0; i < n;i++){
        cerr<<val[i]<<" ";
        ans += val[i];
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