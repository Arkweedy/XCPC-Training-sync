#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e6 + 10;
int n,d;
int h[N],s[N];
struct node{int id;ll w;};
void solve()
{
    ll sum=0;
    cin>>n>>d;
    for(int i=1;i<=n;i++) cin>>h[i],sum+=h[i],s[i]=0;
    int tar=sum/n;
    //cout<<tar<<endl;
    int maxd=0;
    int j=1;
    for(int i=1;i<=n;i++)
    {
        while(s[j]==tar&&j<=n) j++;
        while(s[j]<tar&&h[i]&&j<=n)
        {
            //cout<<i<<' '<<j<<endl;
            maxd=max(maxd,abs(j-i));
            if(s[j]+h[i]<tar) s[j]+=h[i],h[i]=0;
            else 
            {
                h[i]-=tar-s[j];
                s[j]=tar;
                j++;
            }
        }
    }
    cout<<(maxd+d-1)/d<<'\n';
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