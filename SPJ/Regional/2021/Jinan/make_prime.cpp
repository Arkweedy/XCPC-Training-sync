#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

bool check(ll x)
{
    for(ll i = 2;i * i <= x;i++){
        if(x % i == 0)return false;
    }
    return true;
}

void solve()
{
    mt19937_64 g(chrono::steady_clock::now().time_since_epoch().count());
    ull x  = 1000;
    for(int i = 3;i <= 17;i++){
        set<ll>st;
        while(st.size() != 10){
            ll r = g() % x;
            //cerr<<r<<endl;
            while(!check(r))r++;
            if(r < x / 10 || r >= x){
                continue;
            }
            st.insert(r);
            //cout<<r<<" ";
        }
        for(auto p : st){
            cout<<p<<" ";
        }
        cout<<endl;
        x *= 10;
    }
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