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
    if(k == n){
        string x(n,'1');
        cout<<x<<endl;
        return;
    }
    string s(n,'0');
    if(k > 0){
        s[0] = '1';
        k--;
    }
    for(int i = 0;i < k;i++){
        s[n - 2 - i] = '1';
    }
    cout<<s<<endl;
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