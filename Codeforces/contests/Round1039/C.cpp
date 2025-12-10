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
    int mi = 1e9 + 10;
    for(int i = 0;i < n;i++){
        if(a[i] > mi * 2 - 1){
            cout<<"No"<<endl;
            return;
        }
        else{
            mi = min(mi,a[i]);
        }
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