#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define el "\n"
const ll N=1e5+5;
//vector<ll> v;
ll a,b,cnt=0;
char p[15][15] ;
void dfs(ll a,ll b)
{
	p[a+1][b]='H';
	p[a+2][b]='H';
	p[a-1][b]='H';
	p[a-2][b]='H';
	p[a][b+1]='H';
	p[a][b+2]='H';
	p[a][b-1]='H';
	p[a][b-2]='H';
}
void solve()
{
	cin>>a>>b;
	for(int i=1;i<=a;i++)
	{
		for(int j=1;j<=b;j++)
		{
			cin>>p[i][j];
		}
	}
	for(int i=1;i<=a;i++)
	{
		for(int j=1;j<=b;j++)
		{
			if(p[i][j]=='P')
			{
				cnt++;
				dfs(i,j);
			}
		}
	}
	cout<<cnt;
}

int main()

{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    //freopen("crystal.in","r",stdin);
    //freopen("crystal.out","w",stdout);
    int T=1;//cin>>T;
    while(T--)
	{
        solve();
    }
    return 0;
}
