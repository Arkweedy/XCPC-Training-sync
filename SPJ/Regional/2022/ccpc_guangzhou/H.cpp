#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.01 14:10:40

void solve()
{
    int n,k;cin>>n>>k;
    set<int>s;
    while(n--){
        int x;cin>>x;
        s.insert(x);
    }
    int i = 0,j = 1;
    while(k--){
        while(s.count(j))j+=2;
        s.insert(j);
        while(s.count(i))i+=2;
        s.insert(i);
    }
    int mex = 0;
    while(s.count(mex))mex++;

    if(mex & 1)cout<<"Bob\n";
    else cout<<"Alice\n";
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