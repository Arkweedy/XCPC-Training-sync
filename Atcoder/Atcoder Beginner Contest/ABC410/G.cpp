#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<ull>v(n);
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0;i < n;i++){
        v[i] = g();
    }
    vector<int>a(n*2);
    for(int i = 0;i < n;i++){
        int x,y;
        cin>>x>>y;
        x--,y--;
        a[x] = a[y] = v[i];
    }
    unordered_map<ull,int>mp;
    int n = 0;
    vector<ull>hs(n * 2);
    for(int i = 0;i < n;i++){
        hs[i] = (i > 0 ? hs[i-1] : 0) ^ a[i];
        if(mp.count(1)) {
            
        }
    }
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