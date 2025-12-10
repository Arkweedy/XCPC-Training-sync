#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int a, x, y;
    cin >> a >> x >> y;
    if(x > y)swap(x, y);
    if(a < x || a > y){
       cout<<"yes"<<endl; 
    }else{
        cout<<"No"<<endl;
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