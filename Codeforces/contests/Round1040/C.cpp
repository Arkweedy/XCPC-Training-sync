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
    vector<pair<int,int>>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a.begin(),a.end());
    int l = 0, r = -1;
    vector<int>ch;
    for(int i = 0;i < n;i++){
        if(a[i].first > r){
            l = a[i].first;
            r = a[i].second;
            ch.push_back(i + 1);
        }
        else{
            if(a[i].second > r){
                ch.push_back(i + 1);
                r = a[i].second;
            }
        }
        cerr<<l<<" "<<r<<endl;
    }
    cout<<ch.size()<<endl;
    for(int i = 0;i < ch.size();i++){
        cout<<ch[i]<<" ";
    }
    cout<<endl;
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