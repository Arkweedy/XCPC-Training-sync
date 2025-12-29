#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
constexpr int N =5e5+10;
//Create time: 2025.12.29 13:10:01
int n,a[N<<1],rk[N<<1],r[N<<1];
vector<int> ve[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i+n]=a[i];
    for(int i=1;i<=n;i++) ve[i].clear();
    for(int i=1;i<=2*n;i++) ve[a[i]].push_back(i);
    a[2*n+1]=n+1;
    r[2*n+1]=2*n+1;
    for(int i=2*n;i;i--)
    {
        r[i]=i+1;
        while(a[r[i]]<=a[i]) r[i]=r[r[i]];
    }
    int s=2*n;
    for(int i=n;i;i--)
    {
        sort(ve[i].begin(),ve[i].end(),[&](int i,int j)
    {
        int ii=r[i],jj=r[j];
        int l1=ii-i,r1=jj-j;
        if(l1!=r1) return l1>r1;
        return rk[ii]<rk[jj];
    });
        while(ve[i].size())
        {
            rk[ve[i].back()]=s--;
            ve[i].pop_back();
        }
    }
    int p=1;
    for(int i=2;i<=n;i++)
        if(rk[i]<rk[p]) p=i;
    int ma=0;
    for(int i=1;i<=n;i++) 
    {
        ma=max(ma,a[p+i-1]);
        cout<<ma<<' ';
    }
    cout<<'\n';
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