#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,k;cin>>n>>k;
    vector<int>p(n);
    for(int i = 0;i<n;i++){
        cin>>p[i];
    }

    vector<int>st(n);

    int mx = 0;
    for(int i=n-1;i>=0 && k;i--){
        if(p[i] < mx){
            st[i]  = 1;
            k--;
        }
        else mx = p[i];
    }
    vector<int>a;
    for(int i=0;i<n;i++){
        if(!st[i])a.push_back(p[i]);
    }

    vector<int>b;
    b.push_back(a[0]);
    for(int i=1;i<a.size();i++){
        if(k>=2){
            k-=2;
            continue;
        }
        else b.push_back(a[i]);
    }
    if(k && b.size() > 1){
        if(st[0]){
            b[1] = min(b[1],p[0]);
        }
        swap(b[0],b[1]);
    }
    cout<<b.size()<<'\n';
    for(auto u:b)cout<<u<<' ';
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