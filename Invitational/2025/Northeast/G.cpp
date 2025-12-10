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
    vector<int>deg(n);
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        deg[u]++;
        deg[v]++;
    }
    for(int i = 0;i < n;i++){
        deg[i] %= 2;
    }
    int cnt = count(deg.begin(),deg.end(),1);
    vector<int>no;
    for(int i = 0;i < n;i++){
        if(deg[i] == 1){
            no.push_back(i);
        }
    }
    int ans = (cnt + 1)/2;
    cout<<ans<<endl;
    if(cnt % 2 == 1){
        no.push_back(no.back());
    }
    for(int i = 0;i < ans;i++){
        cout<<no[i * 2] + 1<<" "<<no[i * 2 + 1] + 1<<endl;
    }
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