#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll a, b;
    cin>>a>>b;
    ll c = abs(a*a - b*b);
    if(c % 2 == 0){
        cout<<(c / 4 - 1) * 3 + 1<<endl;
    }
    else{
        if(c == 3){cout<<1<<endl;}
        else if(c % 4 == 1){
            cout<<(c / 4 - 1) * 3 + 2<<endl;
        }
        else{
            cout<<c / 4 * 3 <<endl;
        }
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