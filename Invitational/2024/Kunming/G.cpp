#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.02 14:52:04

void solve()
{
    int n;
    cin>>n;
    if(n == 1 || n % 4 == 0){
        cout<<"impossible"<<endl;
    }
    else{
        vector<int>a(n);
        iota(a.begin(),a.end(), 0);
        swap(a[0],a[1]);
        for(int i = 4;i < n;i += 4){
            swap(a[i], a[i - 1]);
        }
        for(int i = 0;i < n;i++){
            cout<<a[i]<<" ";
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