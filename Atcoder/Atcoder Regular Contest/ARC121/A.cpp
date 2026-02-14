#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.02.13 14:12

void solve()
{
    int n;
    cin >> n;
    vector<int>x(n), y(n);
    for(int i = 0;i < n;i++){
        cin >> x[i] >> y[i]; 
    }
    vector<int>ix(n), iy(n);
    iota(ix.begin(),ix.end(), 0);
    iota(iy.begin(),iy.end(), 0);  
    sort(ix.begin(),ix.end(), [&](int i, int j)->bool
    {
        return x[i] > x[j];
    });
    sort(iy.begin() ,iy.end(), [&](int i, int j)->bool
    {
        return y[i] > y[j];
    });

    set<int>s;
    s.insert(ix[0]);
    s.insert(ix[1]);
    s.insert(ix[n - 1]);
    s.insert(ix[n - 2]);
    s.insert(iy[0]);
    s.insert(iy[1]);
    s.insert(iy[n - 1]);
    s.insert(iy[n - 2]);
    vector<int>d;
    for(auto u : s){
        for(auto v : s){
            if(u != v){
                d.push_back(max(x[u] - x[v], y[u] - y[v]));
            }
        }
    }
    sort(d.begin(),d.end(), greater<>());
    int ans = d[1];
    cout << ans << endl;
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