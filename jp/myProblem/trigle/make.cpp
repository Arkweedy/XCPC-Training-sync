#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;



void solve()
{
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    int N = 10;
    int n = g() % N + 1, m = g() % N + 1;
    if(n < m)swap(n,m);
    if(n == m)n++;
    int a = n * n - m * m, b = 2 * n * m, c = n * n + m * m;
    vector<int>arr = {a,b,c};
    shuffle(arr.begin(),arr.end(),g);
    cout<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    cout<<tt<<endl;
    while(tt--){
        solve();
    }
    return 0;
}