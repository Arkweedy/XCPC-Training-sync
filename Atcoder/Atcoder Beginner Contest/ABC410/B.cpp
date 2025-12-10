#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>ans(q);
    vector<int>pos(n + 1);
    for(int i = 0;i < q;i++){
        int x;
        cin>>x;
        if(x == 0){
            int p = min_element(pos.begin() + 1,pos.end())- pos.begin();
            ans[i] = p;
            pos[p]++;
        }else{
            ans[i] = x;
            pos[x]++;
        }
    }
    for(int i = 0;i < q;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
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