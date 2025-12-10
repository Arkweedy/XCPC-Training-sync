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
    vector<int>b(m);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < m;i++){
        cin>>b[i];
    }
    int ans = 0;
    multiset<int>s;
    
    for(int i = 0;i < n;i++){
        s.insert(a[i]);
    }
    for(int i = 0;i < m;i++){
        auto p = s.upper_bound(b[i]);
        //ub : prev(s.begin())
        if(p != s.begin()){
            p--;
            s.erase(p);
            ans++;
        }
    }
    cout<<ans<<endl;
    return;

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