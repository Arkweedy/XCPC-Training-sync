#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using ld = long double;
using namespace std;

//K.cpp Create time : 2026.04.07 18:17

int n = 300,m = 0,tot = 2;

vector<pair<int,int>>res;

void dfs(int u,ld s,int op){
    if(s<1){
        dfs(u,1/s,op^1);
        return;
    }
    if(op==0){
        s-=1;
        tot++;
        res.push_back({u,tot});
        if(res.size()<29
    }else{
        res.push_back({u,n});
    }
}

void solve()
{
    int d;cin>>d;

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