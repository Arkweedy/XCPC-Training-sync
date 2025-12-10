#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int a, b, c, d, e, f;
    cin>>a>>b>>c>>d>>e>>f;
    if(a + c == e && b == d && e == b + f){
        cout<<"Yes"<<endl;
    }else if(a + e == c && b == f && c == b + d){
        cout<<"Yes"<<endl;
    }else if(e + c == a && d == f && a == d + b){
        cout<<"Yes"<<endl;
    }else if(b + d == f && a == c && f == a + e){
        cout<<"Yes"<<endl;
    }else if(b + f == d && a == e && d == a + c){
        cout<<"Yes"<<endl;
    }else if(d + f == b && c == f && b == c + a){
        cout<<"Yes"<<endl;
    }else if(a == c && a == e && a == b + d + f){
        cout<<"Yes"<<endl;
    }else if(b == d && b == f && a + c + e == b){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
        return;
    }
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