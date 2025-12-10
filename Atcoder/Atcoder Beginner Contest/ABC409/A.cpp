#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    string a,b;
    cin>>n>>a>>b;
    int flg = false;
    for(int i = 0;i < n;i++){
        if(a[i] == 'o' && b[i] == 'o'){
            flg = 1;
        }
    }
    cout<<(flg ? "Yes":"No")<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}