#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

pair<ll,ll>Simigcd(ll a,ll b,ll c,ll d)
{
    if(a < b && c > d){
        return {1,1};
    }else{
        ll k = d / c;
        auto res = Simigcd(d % c, c, b - a * k, a);
        res.first += res.second * k;
        swap(res.first,res.second);
        return res;
    };
}

bool solve()
{
    int a,b,c,d;
    if(cin>>a>>b>>c>>d){
        auto res = Simigcd(a,b,c,d);
        cout<<res.first<<"/"<<res.second<<endl;
        return true;
    }else{
        return false;
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(solve()){
        ;
    }
    return 0;
}