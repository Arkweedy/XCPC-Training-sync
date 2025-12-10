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
    if(a[0] > a[n - 1]){
        reverse(a.begin(),a.end());
    }
    int ok = 0, ne = 1;
    for(int i = 0;i < n - 1;i++){
        if(abs(a[i] - a[i + 1]) <= 1){
            ok = 1;
        }else if(a[i] > a[i + 1]){
            ne = 0;
        }
    }
    if(ok){
        cout<<0<<endl;
    }else if(!ne){
        cout<<1<<endl;
    }else{
        cout<<-1<<endl;
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