#include<bits/stdc++.h>
#define N 100009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using namespace std;
using ll =long long ;
const ll INF =1e18;
const int mod=998244353;
int n;
void solve()
{
    cin>>n;
    int k=n%4;
    if(k&1) cout<<-1<<'\n';
    else 
    {
        if(k==0)
        {
            if(n==4)
            {
                cout<<"0 0 0\n0 1 0\n1 1 0\n1 0 0\n1\n";
            }
            else 
            {

                for(int i=1;i<=n/4;i++) cout<<"0 0 0\n0 1 0\n1 1 0\n1 0 0\n";
                cout<<"inf"<<'\n';
            }
        }
        else 
        {
            if(n==6)
            {
                cout<<"0 0 0\n1 0 0\n1 1 0\n1 1 1\n0 1 1\n0 1 0\n2\n";
            }
            else if(n==2) cout<<-1<<'\n';
            else 
            {
                for(int i=1;i<=n/4-1;i++) cout<<"0 0 0\n0 1 0\n1 1 0\n1 0 0\n";
                cout<<"0 0 0\n1 0 0\n1 1 0\n1 1 1\n0 1 1\n0 1 0\n";
                cout<<"inf"<<'\n';
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    cin>>tt;
    while(tt--) solve();
    return 0;
}