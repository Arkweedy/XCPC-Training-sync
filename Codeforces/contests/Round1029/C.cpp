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
    vector<map<int,int>>all(n);
    all[0][a[0]] = 1;
    int p = 0;
    for(int i = 1;i < n;i++){
        all[p+1][a[i]] = 1;
        if(all[p].count(a[i])){
            all[p].erase(a[i]);
        }
        if(all[p].size() == 0)p++;
    }
    cout<<p+1<<endl;
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