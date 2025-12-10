#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, m;
    cin>>n>>m;
    if(n > m)swap(n,m);
    if(n == 1){
        cout<<"No"<<endl;
    }
    else if(n == 2){
        if(m == 2){
            cout<<"No"<<endl;
        }
        else{
            cout<<"yes"<<endl;
        }
    }else{
        cout<<"Yes"<<endl;
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