#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll l, r, k;
    cin>>l>>r>>k;
    ll x = 1;
    while(x * k < l){
        x *= k;
    }
    if(x * k > r){
        cout<<-1<<endl;
    }
    else{
        int tot = 0;
        if(l == 1)cout<<1<<" ",tot++;
        while(x <= r / k){
            if(x * k > r)break;
            x *= k;
            cout<<x<<" ";
            tot++;
        }
        if(tot)cout<<endl;
        else cout<<-1<<endl;

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