#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    vector<int>samax(n + 1);
    for(int i = n - 1;i > 0;i--){
        samax[i] = max(samax[i + 1],a[i]);
    }
    for(int i = 1;i < n;i++){
        b[i] = min(b[i],b[i - 1]);
    }
    
    set<int>st;
    int ans = 0;
    for(int i = 0;i < n;i++){
        st.insert(a[i]);
        int mi = max(*st.begin(), samax[i + 1]);
        if(st.size() > 1)mi = min(mi,*next(st.begin()));
        int p = lower_bound(b.begin(),b.end(),mi,greater<>()) - b.begin();
        cerr<<mi<<" "<<p<<endl;
        if(p + i + 1 > n)break;
        else ans = i + 1;
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