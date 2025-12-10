#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,p,q;
    cin>>n>>m>>p>>q;
    if(n % p == 0){
        if(1ll * n / p * q == m){
            cout<<"Yes"<<endl;
        }else{
            cout<<"No"<<endl;
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