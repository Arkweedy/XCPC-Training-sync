#include<bits/stdc++.h>

using ll = long long;
using ld = long double;

using namespace std;

void solve()
{
    int n;
    cin>>n;
    vector<ld>p(n);
    for(int i = 0;i < n;i++){
        cin>>p[i];
    }

    ld ans = 0;
    for(int i = 0;i < n;i++){//choose i
        for(int j = i + 1;j < n;j++){
            ans += (p[i] * p[j] * 2) / (p[i] + p[j]);
        }
    }
    //ans /= (n);
    cout<<fixed<<setprecision(16)<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}