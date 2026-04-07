#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;

using namespace std;
vector<long double > ve;
void dfs(int p,long double f){

    if(p>21){
        ve.push_back(f);return ;
    }
    dfs(p+1,f);
}
void solve()
{ 
    long double a=0;
    dfs(2,0);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}