#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.24 10:25:35
ll n,k,m;
int mp[300],vis[100];
char cc[300];
void pre()
{
    int cnt=0;
    for(int i='0';i<='9';i++) cc[cnt]=i,mp[i]=cnt++;
    for(int i='A';i<='Z';i++) cc[cnt]=i,mp[i]=cnt++;
}
void solve()
{
    cin>>n>>k>>m;
    for(int i=0;i<n;i++) vis[i]=1;
    for(int i=1;i<=m;i++) 
    {
        char c;cin>>c;
        vis[mp[c]]=0;
    }
    vector<char > ve;
    for(int i=0;i<n;i++) 
        if(vis[i]) ve.push_back(cc[i]);
    n=ve.size();
    string ans;
    while(k)
    {
        ans+=ve[k%n];
        k/=n;
    }
    reverse(ans.begin(),ans.end());
    cout<<ans<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    pre();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}