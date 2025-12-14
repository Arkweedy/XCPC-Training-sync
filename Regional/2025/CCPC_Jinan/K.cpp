#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 5e5 + 10;

int a[N],n;
vector<int> ve[N];
int p[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) ve[i].clear(),p[i]=0;
    for(int i=1;i<=n;i++) cin>>a[i],ve[a[i]].push_back(i);
    int ans=0;
    vector<int> v2,v1;
    for(int i=1;i<=n;i++)
    {
        if(ve[i].size()==0) v2.push_back(i);
    
    for(int i=1;i<=n;i++)
        if(ve[a[i]].size()==1) v1.push_back(a[i]);
    for(int i=1;i<=n;i++)
       if(ve[i].size()==2)
        {
            int l=ve[i][0],r=ve[i][1];
            if(l==1) ans++;
            else p[l-1]=p[r-1]=v2.back(),v2.pop_back();
        }
    assert(v2.size()<=1);
    if(v2.size()) v2.push_back(v2.back());
    for(auto p:v1) v2.push_back(p);
    reverse(v2.begin(),v2.end());
    for(int i=1;i<=n;i++)
        if(!p[i]) p[i]=v2.back(),v2.pop_back();
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++) cout<<p[i]<<' ';
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
