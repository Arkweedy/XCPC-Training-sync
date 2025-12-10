#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>a(n);
    for(int i = 0; i < n;i++){
        cin>>a[i];
    }
    priority_queue<int>pq;
    for(int i = 0;i < m - 1;i++){
        pq.push(a[i]);
    }
    for(int i = m - 1;i < n;i++){
        pq.push(a[i]);
        cout<<pq.top()<<" ";
        pq.pop();
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