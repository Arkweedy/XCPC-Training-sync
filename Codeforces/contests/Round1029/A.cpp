#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, x;
    cin>> n >> x;
    vector<int>a(n);
    for(int i =0;i < n;i++){
        cin>>a[i];
    }
    int l = 0 ,r = 0;
    for(int i = 0;i < n;i++){
        if(a[i] == 1){
            l = i;
            break;
        }
    }
    for(int i = n - 1;i >= 0;i--){
        if(a[i] == 1){
            r = i;
            break;
        }
    }
    if(r - l < x){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
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