#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    map<int,ll>mp;
    int q;
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            int x,y;
            cin>>x>>y;
            mp[x] += y;
        }
        else{
            int x;
            cin>>x;
            if(mp.count(x)){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
    for(auto [x,y] : mp){
        cout<<x<<" "<<y<<endl;
    }
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