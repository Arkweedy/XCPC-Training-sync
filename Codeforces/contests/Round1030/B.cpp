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
    vector<array<int,3>>ans;
    for(int i = 2;i <= n;i++){
        ans.push_back({i,1, i - 1});
        ans.push_back({i,i,n});
    }
    ans.push_back({1,1,n});
    cout<<ans.size()<<endl;
    for(int i = 0;i < ans.size();i++){
        cout<<ans[i][0]<<" "<<ans[i][1]<<" "<<ans[i][2]<<endl;
    }
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