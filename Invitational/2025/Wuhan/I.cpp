#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.31 15:07:07

void solve()
{
    int n,k;
    cin>>n>>k;
    if(k < n){
        cout<<"No"<<endl;
    }
    else if(k > n * n - (n - 1)){
        cout<<"No"<<endl;
    }
    else{
        vector<vector<int>>a(n,vector<int>(n));
        a[0][0] = k;
        int l = 1;
        int r = n * n;
        for(int i = 1;i < n;i++){
            a[i][0] = l++;
            //a[0][i] = l++;
            a[i][i] = r--;
        }
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(l == k)l++;
                if(a[i][j] == 0){
                    a[i][j] = l++;
                }
            }
        }
        cout<<"Yes"<<endl;
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
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