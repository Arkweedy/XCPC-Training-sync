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
    int x = -1;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        if(a[i] != -1)x= a[i];
    }
    //mi == 0
    if(x == -1){
        cout<<"Yes"<<endl;
        return;
    }
    else{
        if(x == 0){
            cout<<"No"<<endl;
            return;
        }
        else if(count(a.begin(),a.end(),-1) + count(a.begin(),a.end(),x) == n){
            cout<<"Yes"<<endl;
            return;
        } 
        else{
            cout<<"No"<<endl;
            return;
        }
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