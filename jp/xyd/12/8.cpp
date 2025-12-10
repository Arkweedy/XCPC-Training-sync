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
    vector<set<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].insert(v);
        g[v].insert(u);
    }
    vector<int>a(n);//maybe illegal
    for(int i = 0;i < n;i++){
        cin>>a[i];
        a[i]--;
    }
    queue<int>q;
    q.push(a[0]);
    for(int i = 1;i < n;i++){
        int p = q.front();
        if(g[p].count(a[i])){
            g[p].erase(a[i]);
            g[a[i]].erase(p);
            q.push(a[i]);
            //cerr<<p + 1<<" find "<<a[i] + 1<<endl;
        }
        else{
            //cerr<<p + 1<<" not find "<<a[i] + 1<<endl;
            cout<<"No"<<endl;
            return;
        }
        while(!q.empty() && g[p].empty()){//clear
            q.pop();
            p = q.front();
        };
    }
    cout<<"Yes"<<endl;
    return;
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