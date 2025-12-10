#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int x,y;cin>>x>>y;
    cout<<x<<endl;
    for(int i=2;i<=x/i;i++){
        if(x%i==0){
            cout<<i<<' ';
            while(x%i==0)x/=i;
        }
    }
    if(x>1)cout<<x<<' ';
    cout<<endl;
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