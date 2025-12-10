#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    if(count(a.begin(),a.end(),0) != 0){
        cout<<"NO"<<endl;
        return;
    }
    int dis = 0;
    for(int i = 0;i < n - 1;i++){
        dis += 2 - a[i];
    }
    if(dis <= a[n - 1]){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
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