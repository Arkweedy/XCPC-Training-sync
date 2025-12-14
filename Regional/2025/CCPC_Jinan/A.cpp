#include<bits/stdc++.h>

using ull = unsigned long long;
using namespace std;

constexpr int N = 1e5 + 10;
ull a,b;
ull s[N];
int p[N];
int check(ull a,int p) //  a/(1<<p)?
{
    if(p<64) return a%(1ull<<p)==0;
    return a==0;
}
void solve()
{
    cin>>a>>b;
    if(a&1)
    {
        s[0]=a;
        for(int i=1;i<=64;i++) s[i]=s[i-1]*s[i-1];
        for(int i=0;i<=64;i++) s[i]--;
        assert(s[63]==0);
        int g=0;
        for(int i=1;i<=64;i++)
        {
            while(!check(s[g],i)) g++;
            p[i]=g;
        }
        for(int i=0;i<=64;i++) s[i]++;
        if(b==1)
        {
            cout<<0<<'\n';return ;
        }
        if(b%2==0)
        {
            cout<<"broken message\n";return ;
        }
        ull ans=0,now=1;
    //    for(int i=0;i<=64;i++) cout<<p[i]<<' ';
        for(int i=2;i<=64;i++)
        {
            //cout<<i<<' '<<ans<<endl;
            if(p[i]==p[i-1]) 
            {
                if(!check(now-b,i)) {cout<<"broken message\n";return ;}
            }
            else 
            {
                assert(p[i]==p[i-1]+1);
                //cerr<<1<<a<<' '<<b<<' '<<i<<endl;
                if(!check(now-b,i)) ans+=(1ull<<p[i-1]),now*=s[p[i-1]];
                if(!check(now-b,i)){cout<<"broken message\n";return ;}
            }
        }
    //    cout<<now<<' '<<b<<endl;
        cout<<ans<<'\n';
        
    }
    else 
    {
        ull g=1;
        for(int i=0;i<=65;i++)
        {
            if(g==b) 
            {
                cout<<i<<'\n';
                return ;
            }
            g*=a;
        }
        cout<<"broken message\n";
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
