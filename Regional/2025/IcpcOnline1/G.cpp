#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e5 + 10;


void solve()
{
    int n, m;
    cin>>n >> m;
    vector<int>a(n);
    for(int i = 0;i <m;i++){
        int u,v;
        cin>>u>>v;
        if(v == u + 1){
            a[u] = 1;
        }
    }
    
//    for(int i = 1;i < n;i++){
//        cerr<<a[i]<<' ';
//    }
//    cerr<<endl;
    
    for(int i = 1;i < n;i++){
        if(!a[i]){
            cout<<"No"<<"\n";
            return;
        }
    }
    cout<<"Yes"<<"\n";
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
