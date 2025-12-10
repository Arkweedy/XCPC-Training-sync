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
    vector<vector<int>>a(n,vector<int>(n));
    int mid = (n - 1) / 2;
    int tot = 0;
    for(int i = 1;i <= n;i++){
        if(i % 2 == 1){//lu
            int p = mid - i / 2;
            for(int j = 0;j < i - 1;j++){
                a[p][p + 1 + j] = tot++;
            }
            for(int j = 0;j < i - 1;j++){
                a[p + 1 + j][p] = tot++;
            }
            a[p][p] = tot++;
        }else{//rd
            int p = mid + i / 2;
            for(int j = 0;j < i - 1;j++){
                a[p][p - 1 - j] = tot++;
            }
            for(int j = 0;j < i - 1;j++){
                a[p - 1 - j][p] = tot++;
            }
            a[p][p] = tot++;
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout<<a[i][j]<<" ";
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