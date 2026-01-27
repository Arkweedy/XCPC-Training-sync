#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.24 10:25:35
int n,k,p[100009];
string sp,sn;
void solve()
{
    cin>>k>>n;
    cin>>sn;
//    return ;
    vector<vector<int>> a,b,na,nb;
    vector<int> v;
    for(int i=0;i<k;i++) v.push_back(i);
    na.push_back(v);nb.push_back(v);
    for(int i=2;i<=n;i++)
    {
        sp=sn;
        cin>>sn;
        a=na,b=nb;
        na.clear();nb.clear();
        int s=a.size();
        //cerr<<s<<endl;
        for(int i=0;i<s;i++)
        {
            vector<int> f[2],t[2];
            for(auto p:a[i]) 
               f[sp[p]-'0'].push_back(p);
            for(auto p:b[i]) 
                t[sn[p]-'0'].push_back(p);
            if(f[0].size()!=t[0].size())
            {
                cout<<"NO\n";return ;
            }
            for(int i=0;i<2;i++) 
                if(f[i].size()) na.push_back(f[i]),nb.push_back(t[i]);
        }
    }
    int s=na.size();
    for(int i=0;i<s;i++)
    {
        int m=na[i].size();
        for(int j=0;j<m;j++) p[na[i][j]]=nb[i][j];
    }
    cout<<"YES\n";
    for(int i=0;i<k;i++) cout<<p[i]+1<<' ';
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