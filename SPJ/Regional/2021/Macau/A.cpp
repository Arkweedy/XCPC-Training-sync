#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N =100;
int n,a[N][N];
void solve()
{
    vector<int> ans;
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) cin>>a[i][j];
    for(int i=1;i<=n;i++)
    {
        if(i&1)
        {
            for(int j=1;j<=n;j++) ans.push_back(a[i][j]);
        }
        else 
        {
            for(int j=n;j;j--) ans.push_back(a[i][j]);
        }
    }
    int cnt=0;
    for(int i=0;i<n*n-1;i++) 
        if(ans[i]>ans[i+1]) cnt++;
    if(cnt<(n*n-1-cnt)) reverse(ans.begin(),ans.end());
//    cout<<cnt<<endl;
    for(auto p:ans) cout<<p<<' ';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}

