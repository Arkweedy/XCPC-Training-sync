#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 1e9 + 7;

void solve()
{
    int n;
    int a1;
    cin >> n >> a1;
    vector<int>l(n);
    for(int i = 0;i < n;i++){
        cin >> l[i];
    }
    ll c1 = l[0],c2 = 0,c3 = 0;
    for(int i = 1;i < n;i++){
        ll nc1,nc2,nc3;
        if(i % 2 == 0){//1
            nc1 = l[i] * (c1 + c2 + c3) + c1;
            nc2 = 0;
            nc3 = c2 + c3;
        }
        else{//2
            nc2 = l[i] * (c1 + c2 + c3) + c2;
            nc1 = 0;
            nc3 = c1 + c3;
        }
        c1 = nc1 % P;
        c2 = nc2 % P;
        c3 = nc3 % P;
    }
    ll ans = (c1 + c2 + c3) % P;
    cout<<ans<<endl;
    return;
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