#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;


void solve()
{
    int n,k;cin>>n>>k;
    for(int i=k;i;i+=k-1){
        assert(i<=n);
        cout<<i<<' '<<i<<endl;
        int a;cin>>a;
        if(a==1) return ;
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
