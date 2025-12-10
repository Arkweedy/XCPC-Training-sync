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
        a[i] = abs(a[i]);
    }
    int m = a[0];
    sort(a.begin(),a.end());
    int p = lower_bound(a.begin(),a.end(),m) - a.begin();
    if(p <= n / 2){
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