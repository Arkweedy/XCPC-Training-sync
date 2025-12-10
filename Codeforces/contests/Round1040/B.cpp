#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,s;
    cin>>n>>s;
    vector<int>a(n);
    int sum = 0;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        sum += a[i];
    }
    if(sum > s){
        for(int i = 0;i < n;i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
    }
    else if(sum == s){
        cout<<-1<<endl;
    }
    else{
        int d = s - sum;
        if(d == 1){
            //021
            int x = count(a.begin(),a.end(),0);
            int y = count(a.begin(),a.end(),1);
            int z = count(a.begin(),a.end(),2);
            vector<int>ans;
            for(int i = 0;i < x;i++){
                ans.push_back(0);
            }
            for(int i = 0;i < z;i++){
                ans.push_back(2);
            }
            for(int i = 0;i < y;i++){
                ans.push_back(1);
            }
            for(int i = 0; i < n;i++){
                cout<<ans[i]<<" "; 
            }
            cout<<endl;
        }
        else {
            cout<<-1<<endl;
        }
    }
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