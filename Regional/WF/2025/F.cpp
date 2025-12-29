#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
constexpr int N =2e5+10;
using namespace std;

//Create time: 2025.12.25 13:43:35
int n,m,k,p,use[N],num;
vector<int> love[N],ve[N];
void solve()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) love[i].clear();
    for(int i=1;i<=m;i++) ve[i].clear();
    for(int i=1;i<=m;i++) use[i]=0,num=0;
    for(int i=1;i<=n;i++)
    {
        cin>>p;
        ve[p].push_back(i);
        cin>>k;
        for(int ii=1;ii<=k;ii++)
        {
            int a;cin>>a;
            love[i].push_back(a);
        }
    }
    map<int,int> mp;
    for(int i=m;i;i--)
    {
        int g=ve[i].size();
        if(!g) continue;
        mp.clear();
        for(auto v:ve[i])
            for(auto g:love[v])
                if(!use[g]) mp[g]++;
        int ok=0;
        for(auto [v,id]:mp)
            if(id==g) ok=1;
        for(auto [v,id]:mp)
        {
            if(!v) continue;
            num++;use[v]=1;
        }
        if(!ok)
        {
            cout<<"no\n";return ;
        }
        if(num>m-i+1)
        {
            cout<<"no\n";return ;
        }
    }
    cout<<"yes\n";
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