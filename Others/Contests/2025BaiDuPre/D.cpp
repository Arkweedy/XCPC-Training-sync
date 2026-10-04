#include<bits/stdc++.h>

using ll = long long;
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int>ans(n + 1);
    if(n % 2 == 1){
        iota(ans.begin(),ans.end(), 0);
    }
    else{
        for(int i = 1;i <= n;i++){
            if(i % 2 == 1){
                ans[i] = i + 1;
            }
            else{
                ans[i] = i - 1;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
