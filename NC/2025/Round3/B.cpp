#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    uint a, b, c;
    cin>>a>>b>>c;
    vector<int>ans;
    auto op1 = [&]()->void
    {
        a <<= 1;
        ans.push_back(1);
    };
    auto op2 = [&]()->void
    {
        b >>= 1;
        ans.push_back(2);
    };
    auto op3 = [&]()->void
    {
        a ^= b;
        ans.push_back(3);
    };
    auto op4 = [&]()->void
    {
        b ^= a;
        ans.push_back(4);
    };

    if(a == 0 && b == 0){
        if(c == 0){
            cout<<0<<endl;
            cout<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
    else{
        if(__countl_zero(a) < __countl_zero(b)){
            op4();
        }
        int p = 31 - __countl_zero(b);
        for(int i = 30;i >= p;i--){
            if((a >> p & 1) ^ (c >> i & 1)){
                op3();
            }
            if(i != p){
                op1();
            }
        }
        for(int i = p - 1;i >= 0;i--){
            op2();
            if((a ^ c) >> i & 1){
                op3();
            }
        }
        op2();
        op4();
        //cerr<<a<<" "<<b<<" "<<c<<endl;
        assert(a == b && b == c);
        assert(ans.size() <= 64);
        cout<<ans.size()<<endl;
        for(int i = 0;i < ans.size();i++){
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }

    return;
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