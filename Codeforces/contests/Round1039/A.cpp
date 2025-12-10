#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, c;
    cin>>n>>c;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    int ans = 0;
    while(!a.empty()){
        sort(a.begin(),a.end());
        vector<ll>b;
        for(int i = 0;i < a.size();i++){
            if(a[i] <= c){
                b.push_back(a[i]);
            }
            else{
                ans++;
            }
        }
        if(!b.empty()){
            b.pop_back();
            //ans++;
        }
        a.clear();
        for(int i = 0;i < b.size();i++){
            a.push_back(b[i] * 2);
        }
    }
    cout<<ans<<endl;
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