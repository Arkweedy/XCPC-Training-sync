#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;
int n,m,a;
void solve()
{
    cin>>n>>m;
    vector<int> ve;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        if(a){
            ve.push_back(a);
        }
        else m--;
    }
    n=ve.size();
    if(m<0) {cout<<"Impossible\n";return ;}
    if(m==n){cout<<"Richman\n";return ;}
    ll ans=0,mi=2e9;
    for(int i=0;i<m;i++) ans+=ve[i];
    for(int i=m;i<n;i++) mi=min(mi,1ll*ve[i]);
    ans+=mi-1;
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
