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
    vector<int>a(n),clr(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    map<int,vector<int>>mp;
    for(int i = 0;i < n;i++){
        cin>>clr[i];
        mp[clr[i]].push_back(a[i]);
    }

    ll ans = 0;
    for(auto [x, arr] : mp){
        vector<int>st;
        for(auto e : arr){
            if(st.empty() || e >= st.back()){
                st.push_back(e);
            }
            else{
                int p = upper_bound(st.begin(),st.end(), e) - st.begin();
                st[p] = e;
            }
        }
        ans += 1ll * (arr.size() - st.size()) * x;
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