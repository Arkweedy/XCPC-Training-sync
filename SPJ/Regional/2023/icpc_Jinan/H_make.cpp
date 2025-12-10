#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.06 17:33:45

void solve()
{
    ofstream fout("H.in");
    fout<<1<<endl;
    fout<<200000<<endl;
    fout<<1<<" "<<2<<" ";
    for(int i = 3;i <= 200000;i+=3){
        fout<<"1 1 2 ";
    }
    fout<<endl;
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