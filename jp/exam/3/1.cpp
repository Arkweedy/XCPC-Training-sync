#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ull n;
    cin>>n;
    int up = -1;
    for(int i = 63;i >= 0;i--){
        if(n >> i & 1){
            up = i;
            break;
        }
    }
    vector<ull>ans;
    ans.push_back(n);
    for(int i = 0;i <= up;i++){
        if(!(n >> i & 1))
        ans.push_back(n ^ (1ull << i));
    }
    sort(ans.begin(),ans.end(),greater<ull>());
    for(auto x : ans){
        cout<<x<<" ";
    }
    cout<<endl;
    return;
}

int main()
{
    //freopen("bin.in","r",stdin);
    //freopen("bin.out","w",stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}