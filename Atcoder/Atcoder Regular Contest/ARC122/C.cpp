#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 20:31:42

void solve()
{
    ll n;
    cin>>n;

    vector<ll>fib(130);
    constexpr ll N = 1e18;
    //87 -> 1.1e18
    fib[0] = fib[1] = 1;
    for(int i = 2;i < 87;i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    vector<int>pos;
    ll m = n;
    for(int i = 86;i >= 0;i--){
        if(n >= fib[i]){
            n -= fib[i];
            pos.push_back(i);
        }
    }

    ll x = 0,y = 0;
    vector<int>ans;
    auto op1 = [&]()->void
    {
        ans.push_back(1);
        x++;
        return;
    };

    auto op2 = [&]()->void
    {
        ans.push_back(2);
        y++;
        return;
    };

    auto op3 = [&]()->void
    {
        ans.push_back(3);
        x += y;
        return;
    };

    auto op4 = [&]()->void
    {
        ans.push_back(4);
        y += x;
        return;
    };

    // for(auto& x : pos){
    //     cerr<<x<<" "<<fib[x]<<endl;
    // }
    

    int steps = pos[0];
    int p = 0;
    for(int i = 0;i <= steps;i++){
        if(p < pos.size() && steps == pos[p] + i){
            if(pos[p] % 2 == 0)op1();
            else op2();
            p++;
        }
        if(i % 2 == 0){
            op4();
        }
        else{
            op3();
        }
    }
    //cerr<<x<<" "<<y<<" "<<m<<endl;

    assert(x == m);

    cout<<ans.size()<<endl;
    for(auto x : ans){
        cout<<x<<"\n";
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