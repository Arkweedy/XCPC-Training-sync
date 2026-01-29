#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 11:03:07

int n;
int ask(vector<int> ve)
{
    vector<int> v(n+1);
    for(auto p:ve) v[p]=1;
    cout<<'?'<<' ';
    for(int i=1;i<=n;i++) cout<<v[i];
    cout<<endl;
    int num;cin>>num;
    return num;
}
vector<int> now;
int D;
int vis[201];
vector<int> operator +(vector<int> a,vector<int> b)
{
    vector<int> ans;
    for(auto p:a) ans.push_back(p);
    for(auto p:b) ans.push_back(p);
    return ans;
}
int add()
{   
    D=ask(now);
    if(!D) return 0;
    for(int i=1;i<=n;i++) vis[i]=0;
    for(auto p:now) vis[p]=1;
    vector<int> v;
    for(int i=1;i<=n;i++)
        if(!vis[i]) v.push_back(i);
    while(v.size()>1)
    {
        int m=v.size()/2;
        vector<int> vl,vr;
        for(int i=0;i<v.size();i++)
        {
            if(i<m) vl.push_back(v[i]);
            else vr.push_back(v[i]);
        }
        if(D+ask(vl)!=ask(now+vl)) v=vl;
        else v=vr;
    }
    now.push_back(v[0]);
    return 1;
}
void answer(int p)
{
    cout<<"! "<<p<<endl;
}
void solve()
{
    cin>>n;
    now.push_back(1);
    
    for(int i=1;i<n;i++)
    {
        int sit=add();
        if(!sit) {answer(0);return ;}
    }
    answer(1);
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