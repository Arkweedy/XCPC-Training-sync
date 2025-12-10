#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.30 21:26:37

void solve()
{
    int x, y, z;
    cin >> x >> y >> z;
    vector<int>a,b,c;
    int ma = max({x, y, z}), mi = min({x,y,z});
    int cnt1 = 0;
    if(x == ma)cnt1++;
    if(y == ma)cnt1++;
    if(z == ma)cnt1++;
    int cnt2 = 0;
    if(x == mi)cnt2++;
    if(y == mi)cnt2++;
    if(z == mi)cnt2++;

    if(cnt2 == 3 || cnt2 == 2){
        a.resize(max(x, y), 0);
        b.resize(max(x, z), 0);
        c.resize(max(y, z), 0);
    }
    else{//01
        for(int i = 0;i < x - 1;i++){
            a.push_back(0);
            b.push_back(0);
        }
        for(int i = 0;i < y;i++){
            a.push_back(1);
            c.push_back(1);
        }
        b.push_back(1);
        for(int i = 0;i < z - 1;i++){
            b.push_back(0);
            c.push_back(0);
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