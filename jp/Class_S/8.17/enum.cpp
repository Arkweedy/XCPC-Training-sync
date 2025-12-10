#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;



constexpr int V = 5;

void print_binary(int x)
{
    bitset<V>bs = x;
    cout<<bs<<endl;
}

// n 
// 2^n 

void solve()
{
    int n = 5;
    int len = 1 << n;
    for(int i = 0;i < len;i++){
        cout<<"subset of ";
        print_binary(i);
        for(int st = i;st != 0;st = (st - 1) & i){
            print_binary(st);
        }
    }
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