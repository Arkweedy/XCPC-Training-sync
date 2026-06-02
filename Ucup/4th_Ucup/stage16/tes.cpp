#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

int a[200];
void solve()
{
    a[1]=3;
    for(int i=2;i<=170;i++){
        int err=0;
        int s=i+2;
        a[i]=i+2;
        for(int j=1;j<=i;j++)
            if(i%j==0) 
            {
                if(a[j]+a[i/j]<=s) err=1;
                a[i]=min(a[j]+a[i/j],a[i]);
            }
        if(!err) cout<<i<<endl;
        
    //    cerr<<i<<' '<<a[i]<<endl;

    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}