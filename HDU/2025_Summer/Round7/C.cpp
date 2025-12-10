#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    if(count(a.begin(),a.end(),0) == n){
        cout<<"0/0"<<endl;
        return;
    }
    double l = 0, r = 1;
    double eps = 1e-8;
    

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