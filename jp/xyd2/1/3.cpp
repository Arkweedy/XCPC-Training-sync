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
    map<int,int>mp;
    for(int i = 0;i < n;i++){
        int x;
        cin>>x;
        mp[x]++;
    }
    map<int,int>dmp = mp;
    for(auto [x,cnt] : mp){
        dmp[x + 1] -= cnt;
    }
    int ans = 0;
    for(auto [x,dcnt] : dmp){
        if(dcnt > 0)
            ans += dcnt;
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