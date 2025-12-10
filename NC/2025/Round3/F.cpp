#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, a, b;
    cin>>n>>a>>b;
    if(n <= a){
        cout<<"Sayonara"<<endl;
    }
    else{
        n %= (a + b);
        int ans = n;
        if(ans > a)ans = 0;
        cout<<ans<<endl;
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