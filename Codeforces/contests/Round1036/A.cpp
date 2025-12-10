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
    for(int i = 0;i < n - 1;i++){
        if(a[i] > a[i + 1]){
            cout<<"Yes"<<endl;
            cout<<2<<endl;
            cout<<a[i]<<" "<<a[i+1]<<endl;
            return;
        }
    }
    cout<<"No"<<endl;
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