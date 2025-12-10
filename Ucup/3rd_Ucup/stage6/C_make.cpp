#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n = 100;
    cout<<n<<endl;
    for(int i = 1;i <= n - 1;i++){
        cout<<i<<" "<<i + 1<<endl;
    }
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());

    int limit = 5000;
    int xx = 2e6;
    for(int i = 1;i <= n;i++){
        cout<<g() % limit<<" ";
    }
    cout<<endl;
    for(int i = 1;i <= n;i++){
        cout<<g() % xx<<" ";
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