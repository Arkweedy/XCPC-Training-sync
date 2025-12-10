#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;

    if(c == e && a + c == b && d + f == b){
        cout<<"Yes"<<endl;
    }else if(b == d && b == f && a + c + e == f){
        cout<<"Yes"<<endl;
    }else if(a == c + e && b + d == a && d == f){
        cout<<"Yes"<<endl;
    }else if(a == c && a == e && b + d + f == a){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
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