#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int x, y;
    cin>>x>>y;
    if(x == 1 || y == 1){
        if(x == 1 && y == 1){
            cout<<1<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
    else{
        cout<<1<<endl;
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