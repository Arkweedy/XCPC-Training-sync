#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.25 13:43:35
int n;
int query(int i,int p)
{
    cout<<i<<' '<<p<<endl;
    int ans;cin>>ans;
    return ans;
}
int p[100];
void solve()
{
    cin>>n;
    int t;cin>>t;
    for(int i=1;i<=n;i++)
    {
        int s=query(i,0);
        if(s==1) return ;
        while(1)
        {
            int ss=query(i,1);
            if(ss==1) return ;
            if(ss!=s)
            {
                if(ss==s+1) break;
                else 
                {
                    int a=query(i,-1);
                    if(a==1) return ;
                    break;
                }
            }
        }
    }
    int a=query(1,1);
    if(a==1) return ;
    p[1]=n-1;
    for(int i=2;i<=n;i++)
    {
        vector<int> aa(n);
        for(int ii=1;ii<n;ii++) 
        {
            aa[ii]=query(i,1);
            if(aa[ii]==1) return ;
        }

        int a=query(i,1);
        if(a==1) return ;
        int g=1;
        for(int j=2;j<n;j++)
            if(aa[j]>aa[g]) g=j;
        p[i]=g;
    }
    for(int i=1;i<=n;i++)
    {
        int a=query(i,p[i]);
        if(a==1) return ;
    }

    
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