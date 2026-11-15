#include <bits/stdc++.h>
#define N 1000009
using ll = long long;
using i64 = long long;
using namespace std;
int n,m;
int in[N];
vector<int> e[N];
int ans[N];
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) in[i]=0,e[i].clear();
    for(int i=1;i<=m;i++){
        int l,r;cin>>l>>r;
        vector<int> v;
        for(int j=1;j<=r-l+1;j++){
            int x;cin>>x;
            v.push_back(x);
        }
        for(int i=0;i+1<v.size();i++){
            in[v[i+1]]++;
            e[v[i]].push_back(v[i+1]);
        }
    }
    set<int> s;
    for(int i=1;i<=n;i++)
        if(!in[i]) s.insert(i);

    int cnt=0;
    while(s.size()){
        int a=*s.begin();
        s.erase(a);
        ans[a]=++cnt;
        for(auto v:e[a]){
            in[v]--;
            if(!in[v]) s.insert(v);
        }
    }
    if(cnt<n) {cout<<-1<<'\n';return ;}
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    cout<<'\n';
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}