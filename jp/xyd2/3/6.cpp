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
    vector<ll>w(n),s(n);
    for(int i = 0;i < n;i++){
        cin>>w[i]>>s[i];
    }
    vector<int>id(n);
    iota(id.begin(),id.end(),0);
    sort(id.begin(),id.end(),[&](int i, int j)->bool
    {
        return w[i] + s[i] < w[j] + s[j];
    });
    ll sumw = 0;
    ll ans = 0;
    for(int i = 0;i < n;i++){
        int p = id[i];
        ans = max(ans,sumw - s[p]);
        sumw += w[p];
    }
    cout<<max(ans,0ll)<<endl;
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