#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.27 00:45:05

void solve()
{
    int n, k;
    cin>>n>>k;
    if(k == 0){
        if(n < 8){
            cout<<-1<<endl;
        }
        else{
            cout<<"6 5 1 2 7 8 4 3 ";
            for(int i = 9;i <= n;i++){
                cout<<i<<" ";
            }
            cout<<endl;
        }

    }
    else if(k == 1){
        if(n == 1){
            cout<<1<<endl;
        }
        else if(n <= 4){
            cout<<-1<<endl;
        }
        else{
            cout<<"4 1 3 5 2 ";
            for(int i = 6;i <= n;i++){
                cout<<i<<" ";
            }
            cout<<endl;
        }
    }
    else{
        vector<int>ans(n);
        for(int i = 0;i < n - k;i++){
            ans[i] = n - i;
        }
        for(int i = 0;i < k;i++){
            ans[n - k + i] = i + 1;
        }
        for(int i = 0;i < n;i++){
            cout<<ans[i]<<" "; 
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