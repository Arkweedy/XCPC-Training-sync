#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int w,h,a,b;
    cin>>w>>h>>a>>b;
    int x,y,u,v;
    cin>>x>>y>>u>>v;
    if(((x - u) % a ==0 && x != u) || ((y - v) % b == 0 && y != v)) {
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
    return;




    if(x > u){
        swap(x,u);
        swap(y,v);
    }
    if(x + a >= u){
        if(abs(v - y) % b != 0){
            cout<<"No"<<endl;
            return;
        }
    }
    if(y > v){
        swap(x,u);
        swap(y,v);
    }
    if(y + b >= v){
        if(abs(x - u) % a != 0){
            cout<<"No"<<endl;
            return;
        }
    }
    if(abs(v - y) % b != 0 &&abs(x - u) % a != 0){
        cout<<"No"<<endl;
        return;
    }
    cout<<"Yes"<<endl;
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