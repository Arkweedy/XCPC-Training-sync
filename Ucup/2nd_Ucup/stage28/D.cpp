#include<bits/stdc++.h>

using namespace std;

using ll = long long;


constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    int n,m;cin>>n>>m;
    vector<int>a(n),b(m);
    int i = 0;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<m;i++)cin>>b[i];
    for(int j=0;j<m;j++){
        while(i<n && a[i]!=b[j])i++;
        if(i==n){
            cout<<"No\n";
            return;
        }
        i++;
    }
    cout<<"Yes\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}