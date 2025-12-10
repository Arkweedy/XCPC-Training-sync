#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>b(m);
    for(int i = 0;i < m;i++){
        cin>>b[i];
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    //cerr<<"begin"<<endl;
    int p = n - 1;
    ll ans = 0;
    for(int i = 0;i < m;i++){
        if(p + 1 >= b[i]){
            for(int j = p - b[i] + 2;j <= p;j++){
                ans += a[j];
                //cerr<<"add "<<a[j]<<endl;
            }
            p = p - b[i];
        }
        else{
            for(int j = 0;j <= p;j++){
                ans += a[j];
                //cerr<<"add "<<a[j]<<endl;
            }
            p = -1;
            break;
        }
    }
    for(int i = 0;i <= p;i++){
        ans += a[i];
    }

    cout<<ans<<endl;
    return;

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