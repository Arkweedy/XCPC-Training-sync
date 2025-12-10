#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
    int n  =rng()%5+1;
    cout<<n<<endl;
    for(int i=1;i<=n;i++)cout<<rng()%2;
    cout<<endl;
    for(int i=1;i<=n;i++)cout<<rng()%2;
    cout<<endl;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cout<<tt<<endl;
    while(tt--){
        solve();
    }
    return 0;
}